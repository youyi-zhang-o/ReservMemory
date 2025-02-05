#include "rsv_mem_mng/source/include/CRsvMemMng.h"
#include "rsv_mem_mng/source/include/SwdlAdaptor.h"
#include <iostream>

std::unique_ptr<IRsvMemMng> RsvMemMngFactory::Create()
{
    return std::make_unique<CRsvMemMng>();
}

CRsvMemMng::CRsvMemMng()
    : m_baseAddress(nullptr), m_totalSize(0), m_swdlActive(false) {}

bool CRsvMemMng::Initialize(uint8_t* base, size_t size) {
    if (!base || size == 0) {
        return false;
    }
    m_swdlAdaptor = std::make_unique<SwdlAdaptor>();
    m_swdlActive = m_swdlAdaptor->IsInSwdl();
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
                Load(usrId, usrHeader);
            } else if (usrHeader.usr_type() == UsrType::USR_TYPE_RAW_BUFFER) {
                m_freeEndOffset -= usrHeader.capacity();
            }
        }
    }
    return true;
}

void CRsvMemMng::RegUpgradeAdaptorCreateFunc(RsvMemUpgradeAdaptorCreateFunc&& func)
{
    m_upgradeAdaptor = func();
}

RsvMemErrCode CRsvMemMng::RegUsrCreateFunc(const std::map<UsrId, RsvMemUsrCreateFunc>& createFuncMap)
{
    for (auto const& [id, createFunc] : createFuncMap) {
        m_users.emplace(id, createFunc());
    }
    return RsvMemErrCode::RSV_MEM_SUCCESS;
}

std::shared_ptr<IRsvMemUsr> CRsvMemMng::GetUsr(UsrId id) {
    std::lock_guard<std::mutex> lock(m_mutex);
    auto it = m_users.find(id);
    return (it != m_users.end()) ? it->second : nullptr;
}

RsvMemErrCode CRsvMemMng::Upgrade() {
    if (!m_upgradeAdaptor) {
        return RsvMemErrCode::RSV_MEM_FAILURE;
    }
    m_upgradeAdaptor->Initialize({m_baseAddress, m_totalSize});
    for (auto const&[usrId, usr] : m_users) {
        auto iter = m_usrHeaders.usr_headers().find(usrId);
        if (iter == m_usrHeaders.usr_headers().end()) {
            continue;
        }
        if (iter->second.usr_type() != UsrType::USR_TYPE_PROTO) {
            continue;
        }
        RawBuffer buffer;
        if (m_upgradeAdaptor->GetUsrData(usrId, buffer) == RsvMemErrCode::RSV_MEM_SUCCESS) {
            usr->FrameUpgradeRecover(buffer);
        }
    }
    return RsvMemErrCode::RSV_MEM_SUCCESS;
}

void CRsvMemMng::NotifySwdlEnd() {
    if (m_swdlActive) {
        return;
    }
    m_swdlActive = false;
    // TODO: 允许刷新到保留内存 
}

void CRsvMemMng::OnSystemClose() {
    // TODO: 立马刷新到保留内存
}

void CRsvMemMng::Load(UsrId id, const UsrHeader& usrHeader)
{
    auto iter = m_users.find(id);
    if (iter == m_users.end()) {
        return;
    }
    auto usr = iter->second;
    auto msg = usr->GetDataMsg();
    if (!msg) {
        return;
    }
    msg->ParseFromArray(usrHeader.offset() + m_baseAddress, usrHeader.size());
}

void CRsvMemMng::SaveOne(UsrId id, const IRsvMemUsr &usr)
{
    auto iter = m_usrHeaders.usr_headers().find(id);
    if (iter == m_usrHeaders.usr_headers().end()) {
        return;
    }
    auto& usrHeader = iter->second;
    (void)usrHeader;
    // TODO
}

void CRsvMemMng::SaveAll()
{
    std::lock_guard lock(m_mutex);
    for (auto const& [usrId, usr] : m_users) {
        auto msg = usr->GetDataMsg();
        if (msg && usr->m_isDirty) {
            std::vector<uint8_t> buffer(msg->ByteSizeLong());
            msg->SerializeToArray(buffer.data(), buffer.size());
            // TODO: 保存到保留内存 扩容和内存整理操作
        }
    }
}

bool CRsvMemMng::SaveHeader()
{
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
