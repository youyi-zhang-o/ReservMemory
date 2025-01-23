#include "rsv_mem_mng/source/include/CRsvMemMng.h"
#include <cstring>
#include <iostream>
#include <Kernel/string.h>

CRsvMemMng::CRsvMemMng()
    : m_baseAddress(nullptr), m_totalSize(0), m_swdlActive(false) {}

bool CRsvMemMng::Initialize(uint8_t* base, size_t size) {
    if (!base || size == 0) {
        return false;
    }

    m_baseAddress = base;
    m_totalSize = size;
    m_header = reinterpret_cast<RsvMemHeader*>(m_baseAddress);
    if (m_header->magicTag != RSV_MEM_MAGIC_TAG) {
        std::fill(base, base + size, 0);
        m_header->magicTag = RSV_MEM_MAGIC_TAG;
        m_header->ver = RSV_MEM_VER_CUR;
        m_header->reserved = 0;
        m_freeBeginOffset = sizeof(RsvMemHeader);
        auto usrHeadersSize = m_usrHeaders.ByteSizeLong();
        m_header->usrHeadersCapacity = 2 * usrHeadersSize;
        m_usrHeaders.SerializeToArray(m_baseAddress + m_freeBeginOffset, m_header->usrHeadersCapacity);
        m_freeBeginOffset += m_header->usrHeadersCapacity;
        m_freeEndOffset = m_totalSize;
    } else {
        m_usrHeaders.ParseFromArray(m_baseAddress + sizeof(RsvMemHeader), m_header->usrHeadersCapacity);
        m_freeBeginOffset = sizeof(RsvMemHeader) + m_header->usrHeadersCapacity;
        for (auto const& [usrId, usrHeader] : m_usrHeaders.usr_headers()) {
            if (usrHeader.usr_type() == UsrType::USR_TYPE_PROTO) {
                m_freeBeginOffset += usrHeader.capacity();
            } else if (usrHeader.usr_type() == UsrType::USR_TYPE_RAW_BUFFER) {
                m_freeEndOffset -= usrHeader.capacity();
            }
        }
    }
    return true;
}

void CRsvMemMng::RegUpgradeAdaptorCreateFunc(RsvMemUpgradeAdaptorCreateFunc&& func) {
    m_upgradeAdaptorFunc = std::move(func);
}

RsvMemErrCode CRsvMemMng::RegUsrCreateFunc(UsrId id, RsvMemUsrCreateFunc&& createFunc) {
    if (!createFunc) {
        return RsvMemErrCode::INVALID_ARGUMENT;
    }
    m_usrCreateFunc = std::move(createFunc);
    return RsvMemErrCode::RSV_MEM_SUCCESS;
}

std::shared_ptr<IRsvMemUsr> CRsvMemMng::GetUsr(UsrId id) {
    std::lock_guard<std::mutex> lock(m_mutex);
    auto it = m_users.find(id);
    return (it != m_users.end()) ? it->second : nullptr;
}

RsvMemErrCode CRsvMemMng::RegRawBufferUsr(UsrId id, size_t len) {
    std::lock_guard<std::mutex> lock(m_mutex);

    if (m_usrHeaders.usr_headers().contains(id)) {
        return RsvMemErrCode::USER_ALREADY_EXISTS;
    }

    if (len > m_freeEndOffset - m_freeBeginOffset) {
        return RsvMemErrCode::MEMORY_NOT_ENOUGH;
    }
    m_freeEndOffset -= len;
    UsrHeader header;
    auto [iter, inserted] = m_usrHeaders.mutable_usr_headers()->try_emplace(id);
    if (inserted) {
        iter->second.set_capacity(len);
        iter->second.set_size(len);
        iter->second.set_offset(m_freeBeginOffset);
        iter->second.set_usr_type(UsrType::USR_TYPE_RAW_BUFFER);
    }
    return SaveHeader() ? RsvMemErrCode::RSV_MEM_SUCCESS : RsvMemErrCode::RSV_MEM_INTERNAL_ERROR;
}

RsvMemErrCode CRsvMemMng::GetRawBuffer(UsrId id, RawBuffer& buffer) {
    std::lock_guard<std::mutex> lock(m_mutex);

    auto iter = m_usrHeaders.usr_headers().find(id);
    if (iter != m_usrHeaders.usr_headers().end() && iter->second.usr_type() == UsrType::USR_TYPE_RAW_BUFFER) {
        buffer.data = iter->second.offset() + m_baseAddress;
        buffer.len = iter->second.size();
        return RsvMemErrCode::RSV_MEM_SUCCESS;
    }
    return RsvMemErrCode::RSV_MEM_USER_NOT_ALLOCATED;
}

RsvMemErrCode CRsvMemMng::Upgrade() {
    if (!m_upgradeAdaptorFunc) {
        return RsvMemErrCode::RSV_MEM_UPGRADE_ADAPTOR_NOT_FOUND;
    }

    auto adaptor = m_upgradeAdaptorFunc();
    if (!adaptor) {
        return RsvMemErrCode::RSV_MEM_UPGRADE_FAILED;
    }

    adaptor->Initialize({m_baseAddress, m_totalSize});
    // TODO 升级处理逻辑
    return RsvMemErrCode::RSV_MEM_SUCCESS;
}

bool CRsvMemMng::NotifySwdlEnd() {
    if (!m_swdlActive) {
        return false;
    }

    m_swdlActive = false;
    return FlushCache();
}

void CRsvMemMng::OnSystemClose() {
    FlushCache();
    SaveHeader();
}

bool CRsvMemMng::SaveHeader() {
    auto size = m_usrHeaders.ByteSizeLong();
    if (size > m_header->usrHeadersCapacity) {
        auto newUsrHeaderCapacity = 2 * size;
        auto *dataBegin = m_baseAddress + sizeof(RsvMemHeader) + m_header->usrHeadersCapacity;
        auto *dataEnd = m_baseAddress + m_freeBeginOffset;
        // 扩容到当前容量的两倍 后面的内容往后移
        std::copy_backward(dataBegin, dataEnd, m_baseAddress + sizeof(RsvMemHeader) + newUsrHeaderCapacity);
        m_freeBeginOffset += newUsrHeaderCapacity - m_header->usrHeadersCapacity;
        m_header->usrHeadersCapacity = newUsrHeaderCapacity;
    }
    m_usrHeaders.SerializeToArray(m_baseAddress + sizeof(RsvMemHeader), m_header->usrHeadersCapacity);
    return true;
}

bool CRsvMemMng::FlushCache() {
    // 将缓存中的数据写回到保留内存
    for (const auto& byte : m_cache) {
        // 模拟写入逻辑，实际应更新保留内存
    }
    m_cache.clear();
    return true;
}