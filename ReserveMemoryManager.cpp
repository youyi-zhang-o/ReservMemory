#include "ReserveMemoryManager.h"
#include <algorithm>
#include <cstring>
#include <iostream>
#include <google/protobuf/message.h>

///////////////////////////////////////////////////////////////////////////
// 单例
///////////////////////////////////////////////////////////////////////////
ReserveMemoryManager& ReserveMemoryManager::Instance() {
    static ReserveMemoryManager instance;
    return instance;
}

///////////////////////////////////////////////////////////////////////////
// 构造 & 初始化
///////////////////////////////////////////////////////////////////////////
ReserveMemoryManager::ReserveMemoryManager()
    : m_base(nullptr)
    , m_size(0)
    , m_upgradeStatus(nullptr)
{
    std::memset(&m_header, 0, sizeof(m_header));
}

bool ReserveMemoryManager::Initialize(uint8_t* base, size_t size) {
    if (!base || size < sizeof(MemoryHeader)) {
        std::cerr << "[RMM] Invalid base or size.\n";
        return false;
    }
    m_base = base;
    m_size = size;

    LoadHeader();
    if (m_header.version == 0) {
        // 初始化头部
        std::memset(&m_header, 0, sizeof(m_header));
        m_header.version = 1;
        SaveHeader();
    }
    std::cout << "[RMM] Initialize done. version=" << m_header.version 
              << ", allocated=" << m_header.allocatedBlocks << "\n";
    return true;
}

void ReserveMemoryManager::SetUpgradeStatusChecker(const IDeviceUpgradeStatus* checker) {
    m_upgradeStatus = checker;
}

void ReserveMemoryManager::LoadHeader() {
    std::memcpy(&m_header, m_base, sizeof(m_header));
}

void ReserveMemoryManager::SaveHeader() {
    std::memcpy(m_base, &m_header, sizeof(m_header));
}

///////////////////////////////////////////////////////////////////////////
// Protobuf接口
///////////////////////////////////////////////////////////////////////////
bool ReserveMemoryManager::SaveData(uint32_t configId, const google::protobuf::Message& msg) {
    // 先序列化到临时 raw vector
    int sizeNeeded = msg.ByteSizeLong();
    if (sizeNeeded < 0) return false;

    std::vector<uint8_t> raw(sizeNeeded);
    if (!msg.SerializeToArray(raw.data(), sizeNeeded)) {
        std::cerr << "[RMM] SerializeToArray failed.\n";
        return false;
    }

    // 判断是否升级中
    bool upgrading = (m_upgradeStatus && m_upgradeStatus->IsUpgrading());
    if (upgrading) {
        // 缓存
        PendingWrite w;
        w.configId = configId;
        w.type     = WriteType::Proto;
        w.rawData  = std::move(raw);
        m_pendingWrites.push_back(std::move(w));
        std::cout << "[RMM] SaveData(Proto) -> cached (upgrade in progress).\n";
        return true;
    } else {
        // 直接写
        return CommitWrite(configId, raw);
    }
}

bool ReserveMemoryManager::LoadData(uint32_t configId, google::protobuf::Message& msg) {
    int idx = FindBlockIndex(configId);
    if (idx < 0) return false;
    const auto& blk = m_header.blocks[idx];

    if (blk.usedSize == 0 || (blk.startOffset + blk.usedSize) > m_size) {
        return false;
    }
    const uint8_t* src = m_base + blk.startOffset;
    if (!msg.ParseFromArray(src, blk.usedSize)) {
        std::cerr << "[RMM] ParseFromArray fail in LoadData(Proto).\n";
        return false;
    }
    return true;
}

///////////////////////////////////////////////////////////////////////////
// vector接口
///////////////////////////////////////////////////////////////////////////
bool ReserveMemoryManager::SaveData(uint32_t configId, const std::vector<uint8_t>& data) {
    bool upgrading = (m_upgradeStatus && m_upgradeStatus->IsUpgrading());
    if (upgrading) {
        // 缓存
        PendingWrite w;
        w.configId = configId;
        w.type     = WriteType::RawVector;
        w.rawData  = data;
        m_pendingWrites.push_back(std::move(w));
        std::cout << "[RMM] SaveData(vector) -> cached (upgrade in progress).\n";
        return true;
    } else {
        // 直接写
        return CommitWrite(configId, data);
    }
}

bool ReserveMemoryManager::LoadData(uint32_t configId, std::vector<uint8_t>& outData) {
    int idx = FindBlockIndex(configId);
    if (idx < 0) return false;

    const auto& blk = m_header.blocks[idx];
    if (blk.usedSize == 0 || (blk.startOffset + blk.usedSize) > m_size) {
        return false;
    }
    outData.resize(blk.usedSize);
    std::memcpy(outData.data(), m_base + blk.startOffset, blk.usedSize);
    return true;
}

///////////////////////////////////////////////////////////////////////////
// 指针+大小接口
///////////////////////////////////////////////////////////////////////////
bool ReserveMemoryManager::LoadData(uint32_t configId, uint8_t*& outPtr, size_t& outSize) {
    int idx = FindBlockIndex(configId);
    if (idx < 0) return false;
    const auto& blk = m_header.blocks[idx];
    if (blk.usedSize == 0 || (blk.startOffset + blk.usedSize) > m_size) {
        return false;
    }
    outPtr  = m_base + blk.startOffset;
    outSize = blk.usedSize;
    return true;
}

///////////////////////////////////////////////////////////////////////////
// 升级完成 / 升级失败
///////////////////////////////////////////////////////////////////////////
void ReserveMemoryManager::FinishUpgrade() {
    std::cout << "[RMM] FinishUpgrade => commit " << m_pendingWrites.size() 
              << " writes.\n";
    for (auto& w : m_pendingWrites) {
        CommitWrite(w.configId, w.rawData);
    }
    m_pendingWrites.clear();
}

void ReserveMemoryManager::CancelUpgrade() {
    std::cout << "[RMM] CancelUpgrade => discard " << m_pendingWrites.size() 
              << " writes.\n";
    m_pendingWrites.clear();
}

///////////////////////////////////////////////////////////////////////////
// CommitWrite: 真正写入底层
///////////////////////////////////////////////////////////////////////////
bool ReserveMemoryManager::CommitWrite(uint32_t configId, const std::vector<uint8_t>& data) {
    int idx = AllocateOrExpandBlock(configId, data.size());
    if (idx < 0) {
        std::cerr << "[RMM] CommitWrite fail: can't allocate or expand.\n";
        return false;
    }
    auto& blk = m_header.blocks[idx];
    blk.usedSize = static_cast<uint32_t>(data.size());
    if (!data.empty()) {
        std::memcpy(m_base + blk.startOffset, data.data(), data.size());
    }
    SaveHeader();
    std::cout << "[RMM] CommitWrite configId=" << configId 
              << ", size=" << data.size() << "\n";
    return true;
}

///////////////////////////////////////////////////////////////////////////
// 内部：FindBlockIndex
///////////////////////////////////////////////////////////////////////////
int ReserveMemoryManager::FindBlockIndex(uint32_t ownerId) const {
    for (uint32_t i = 0; i < m_header.allocatedBlocks; ++i) {
        if (m_header.blocks[i].ownerId == ownerId) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

///////////////////////////////////////////////////////////////////////////
// AllocateOrExpandBlock
///////////////////////////////////////////////////////////////////////////
int ReserveMemoryManager::AllocateOrExpandBlock(uint32_t ownerId, size_t neededSize) {
    int idx = FindBlockIndex(ownerId);
    if (idx < 0) {
        // 不存在 => 新分配
        idx = AutoAllocateBlock(ownerId, neededSize);
    } else {
        // 存在 => 扩容
        if (!ExpandBlockIfNeeded(idx, neededSize)) {
            return -1;
        }
    }
    return idx;
}

///////////////////////////////////////////////////////////////////////////
// AutoAllocateBlock (首次分配)
///////////////////////////////////////////////////////////////////////////
int ReserveMemoryManager::AutoAllocateBlock(uint32_t ownerId, size_t neededSize) {
    if (m_header.allocatedBlocks >= 256) {
        return -1; // 超过块数上限
    }
    // 预留最小容量
    size_t capacity = (neededSize < 64) ? 64 : neededSize;

    // 找末尾
    size_t usedEnd = sizeof(MemoryHeader);
    for (uint32_t i = 0; i < m_header.allocatedBlocks; ++i) {
        auto& b = m_header.blocks[i];
        size_t end = b.startOffset + b.capacity;
        if (end > usedEnd) {
            usedEnd = end;
        }
    }
    // 如果末尾放不下 => Compact
    if (usedEnd + capacity > m_size) {
        CompactMemory();
        // 重新计算 usedEnd
        usedEnd = sizeof(MemoryHeader);
        for (uint32_t i = 0; i < m_header.allocatedBlocks; ++i) {
            auto& b = m_header.blocks[i];
            size_t end = b.startOffset + b.capacity;
            if (end > usedEnd) {
                usedEnd = end;
            }
        }
        if (usedEnd + capacity > m_size) {
            return -1; // 还是放不下
        }
    }

    // 分配
    uint32_t idx = m_header.allocatedBlocks;
    m_header.blocks[idx].ownerId     = ownerId;
    m_header.blocks[idx].startOffset = static_cast<uint32_t>(usedEnd);
    m_header.blocks[idx].capacity    = static_cast<uint32_t>(capacity);
    m_header.blocks[idx].usedSize    = 0;
    m_header.allocatedBlocks++;
    SaveHeader();
    return idx;
}

///////////////////////////////////////////////////////////////////////////
// ExpandBlockIfNeeded (倍增策略)
///////////////////////////////////////////////////////////////////////////
bool ReserveMemoryManager::ExpandBlockIfNeeded(int index, size_t neededSize) {
    if (index < 0 || (uint32_t)index >= m_header.allocatedBlocks) {
        return false;
    }
    auto& blk = m_header.blocks[index];
    if (neededSize <= blk.capacity) {
        // 不需扩容
        return true;
    }

    // 倍增
    size_t newCap = blk.capacity;
    while (newCap < neededSize) {
        newCap *= 2;
    }

    // 看后面空余
    size_t currEnd = blk.startOffset + blk.capacity;
    size_t nextBlockStart = m_size;
    for (uint32_t i = 0; i < m_header.allocatedBlocks; ++i) {
        auto& b2 = m_header.blocks[i];
        if (b2.startOffset > blk.startOffset && b2.startOffset < nextBlockStart) {
            nextBlockStart = b2.startOffset;
        }
    }
    size_t gapSize = (nextBlockStart > currEnd) ? (nextBlockStart - currEnd) : 0;
    size_t neededExtra = newCap - blk.capacity;

    if (gapSize >= neededExtra) {
        // 原地扩容
        blk.capacity = static_cast<uint32_t>(newCap);
        SaveHeader();
        return true;
    }

    // 不够 => Compact
    CompactMemory();

    // 重新找自己
    int newIndex = FindBlockIndex(blk.ownerId);
    if (newIndex < 0) return false;
    auto& blk2 = m_header.blocks[newIndex];

    currEnd = blk2.startOffset + blk2.capacity;
    nextBlockStart = m_size;
    for (uint32_t i = 0; i < m_header.allocatedBlocks; ++i) {
        auto& b3 = m_header.blocks[i];
        if (b3.startOffset > blk2.startOffset && b3.startOffset < nextBlockStart) {
            nextBlockStart = b3.startOffset;
        }
    }
    gapSize = (nextBlockStart > currEnd) ? (nextBlockStart - currEnd) : 0;
    neededExtra = newCap - blk2.capacity;

    if (gapSize >= neededExtra) {
        blk2.capacity = static_cast<uint32_t>(newCap);
        SaveHeader();
        return true;
    }

    // 还不够 => 搬到末尾
    size_t usedEnd = sizeof(MemoryHeader);
    for (uint32_t i = 0; i < m_header.allocatedBlocks; ++i) {
        auto& b3 = m_header.blocks[i];
        size_t end = b3.startOffset + b3.capacity;
        if (end > usedEnd) usedEnd = end;
    }
    if (usedEnd + newCap > m_size) {
        // 末尾也不够
        return false;
    }

    size_t oldOff = blk2.startOffset;
    size_t oldSize = blk2.usedSize;
    blk2.startOffset = static_cast<uint32_t>(usedEnd);
    blk2.capacity    = static_cast<uint32_t>(newCap);

    // 搬移已用数据
    if (oldSize > 0) {
        std::memmove(m_base + blk2.startOffset, m_base + oldOff, oldSize);
    }

    SaveHeader();
    return true;
}

///////////////////////////////////////////////////////////////////////////
// CompactMemory
///////////////////////////////////////////////////////////////////////////
void ReserveMemoryManager::CompactMemory() {
    uint32_t n = m_header.allocatedBlocks;
    if (n <= 1) return;
    auto beginIter = &m_header.blocks[0];
    auto endIter   = &m_header.blocks[n];

    // 按 startOffset 排序
    std::sort(beginIter, endIter, [](const BlockInfo& a, const BlockInfo& b){
        return a.startOffset < b.startOffset;
    });

    size_t nextFree = sizeof(MemoryHeader);
    for (uint32_t i = 0; i < n; ++i) {
        auto& blk = m_header.blocks[i];
        if (blk.startOffset > nextFree) {
            std::memmove(m_base + nextFree, m_base + blk.startOffset, blk.usedSize);
            blk.startOffset = static_cast<uint32_t>(nextFree);
        }
        nextFree = blk.startOffset + blk.capacity; // 注意贴紧 capacity
    }
    SaveHeader();
}