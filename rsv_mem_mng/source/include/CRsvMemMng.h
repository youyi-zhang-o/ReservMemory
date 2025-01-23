#pragma once
#include <map>
#include <memory>
#include <vector>
#include <functional>
#include <mutex>
#include "UsrHeader.pb.h"
#include "rsv_mem_mng/include/IRsvMemMng.h"
#include <rsv_mem_mng/include/RsvMemHeader.h>

class CRsvMemMng : public IRsvMemMng {
public:
    CRsvMemMng();
    ~CRsvMemMng() override = default;

    // 初始化保留内存
    bool Initialize(uint8_t* base, size_t size) override;

    // 注册升级适配器创建函数
    void RegUpgradeAdaptorCreateFunc(RsvMemUpgradeAdaptorCreateFunc&& func) override;

    // 注册用户创建函数
    RsvMemErrCode RegUsrCreateFunc(UsrId id, RsvMemUsrCreateFunc&& createFunc) override;

    // 获取用户对象
    std::shared_ptr<IRsvMemUsr> GetUsr(UsrId id) override;

    // 注册原始缓冲区用户
    RsvMemErrCode RegRawBufferUsr(UsrId id, size_t len) override;

    // 获取原始缓冲区
    RsvMemErrCode GetRawBuffer(UsrId id, RawBuffer& buffer) override;

    // 执行升级操作
    RsvMemErrCode Upgrade() override;

    // 通知包加载结束
    bool NotifySwdlEnd() override;

    // 系统关闭通知
    void OnSystemClose() override;

private:
    uint8_t* m_baseAddress { nullptr };                    // 保留内存基地址
    size_t m_totalSize { 0 };                              // 总内存大小
    size_t m_freeBeginOffset { 0 };                        // 空闲空间起始偏移（相对于保留内存基地址）
    size_t m_freeEndOffset { 0 };                          // 空闲空间结束偏移（相对于保留内存基地址 指向空闲的最后一个字节的后一个字节）
    RsvMemHeader* m_header { nullptr };                    // 保留内存头信息
    UsrHeaders m_usrHeaders;                               // protobuf 结构体，用于管理各个用户的内存信息
    std::map<UsrId, std::shared_ptr<IRsvMemUsr>> m_users;  // 已注册的用户
    std::vector<uint8_t> m_cache;                          // 缓存写操作
    bool m_swdlActive;                                     // 是否处于包加载状态
    RsvMemUpgradeAdaptorCreateFunc m_upgradeAdaptorFunc;   // 升级适配器创建函数
    RsvMemUsrCreateFunc m_usrCreateFunc;                   // 用户创建函数
    std::mutex m_mutex;                                    // 线程安全锁（可选）

    // 将头信息保存到保留内存
    bool SaveHeader();

    // 刷新缓存到保留内存
    bool FlushCache();
};