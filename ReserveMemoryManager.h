#pragma once

#include <cstdint>
#include <cstddef>
#include <vector>
#include <string>
#include <google/protobuf/message.h>
#include "IDeviceUpgradeStatus.h"

/**
 * @brief 单个块的信息
 * - ownerId      对应 configId
 * - startOffset  相对于保留内存基址的偏移
 * - usedSize     当前块实际使用大小 (字节)
 * - capacity     当前块分配的容量 (字节)
 */
struct BlockInfo {
    uint32_t ownerId;
    uint32_t startOffset;
    uint32_t usedSize;
    uint32_t capacity;
};

/**
 * @brief 整体头部信息
 * - version
 * - allocatedBlocks
 * - blocks[256]
 */
struct MemoryHeader {
    uint32_t version;
    uint32_t allocatedBlocks;
    BlockInfo blocks[256]; 
};

/**
 * @brief 写操作类型：区分是 Protobuf 还是 原始字节
 */
enum class WriteType {
    Proto,
    RawVector
};

/**
 * @brief 用于缓存写操作的结构体
 */
struct PendingWrite {
    uint32_t configId;
    WriteType type;
    std::vector<uint8_t> rawData;  // 写入的实际序列化字节
};

/**
 * @brief 保留内存管理器：管理自动分配、扩容、序列化写入，集成“升级中写操作缓存”逻辑
 */
class ReserveMemoryManager {
public:
    static ReserveMemoryManager& Instance();

    /**
     * @brief 初始化保留内存
     * @param base 保留内存基地址
     * @param size 保留内存总大小 (字节)
     * @return true if success
     */
    bool Initialize(uint8_t* base, size_t size);

    /**
     * @brief 设置设备升级状态检查器
     */
    void SetUpgradeStatusChecker(const IDeviceUpgradeStatus* checker);

    // =============== Protobuf接口 ===============
    bool SaveData(uint32_t configId, const google::protobuf::Message& msg);
    bool LoadData(uint32_t configId, google::protobuf::Message& msg);

    // =============== 原始字节 vector 接口 ===============
    bool SaveData(uint32_t configId, const std::vector<uint8_t>& data);
    bool LoadData(uint32_t configId, std::vector<uint8_t>& outData);

    // =============== 指针+大小接口 (只读) ===============
    bool LoadData(uint32_t configId, uint8_t*& outPtr, size_t& outSize);

    // =============== 升级完成/取消接口 ===============
    /**
     * @brief 升级成功 => 将缓存写操作一次性写入保留内存
     */
    void FinishUpgrade();

    /**
     * @brief 升级失败 => 丢弃缓存写操作
     */
    void CancelUpgrade();

private:
    ReserveMemoryManager();
    ~ReserveMemoryManager() = default;
    ReserveMemoryManager(const ReserveMemoryManager&) = delete;
    ReserveMemoryManager& operator=(const ReserveMemoryManager&) = delete;

    void LoadHeader();
    void SaveHeader();

    int FindBlockIndex(uint32_t ownerId) const;
    int AllocateOrExpandBlock(uint32_t ownerId, size_t neededSize);
    int AutoAllocateBlock(uint32_t ownerId, size_t neededSize);
    bool ExpandBlockIfNeeded(int index, size_t neededSize);
    void CompactMemory();

    /**
     * @brief 真正将 data 写入 configId 对应块 (分配/扩容后memcpy)
     */
    bool CommitWrite(uint32_t configId, const std::vector<uint8_t>& data);

private:
    MemoryHeader m_header;
    uint8_t*     m_base;
    size_t       m_size;

    // 升级状态检查器(外部设置)
    const IDeviceUpgradeStatus* m_upgradeStatus;

    // 升级模式下缓存的写操作
    std::vector<PendingWrite> m_pendingWrites;
};