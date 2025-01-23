#pragma once

#include <functional>
#include <map>
#include <memory>
#include "pub_def.h"
#include "IRsvMemUsr.h"

/*
# 1. 从老框架升级到新框架
## 1.1 使用者在初始化时判断是否需要进行框架升级，如果需要，则使用 -1 版本的恢复操作从保留内存中恢复数据。恢复数据后调用
    0 版本的保存操作保存，后续读取
*/

class IRsvMemUpgradeAdaptor {
public:
    virtual ~IRsvMemUpgradeAdaptor() = default;
    virtual void Initialize(const RawBuffer& rsvMem) = 0;
    // 一般通过读取保留内存头来判断保留内存是否有效 无效则不进行保留内存升级操作。
    // 进行保留内存升级的条件：软复位 & 确认不是新框架的头 & 确认是老框架的头
    // 对于没有历史遗留问题的新设备 确保这个接口总是返回 false
    virtual bool IsRsvMemValid() = 0;
    // 对每个 User，管理类会调用这个类的GetUsrData接口获取到老的保留内存数据，然后使用 IRsvMemUsr
    // 的 FrameUpgradeRecover 恢复数据到内存中
    // 对于不需要恢复或者无法恢复的 User，需要返回错误码 RSV_MEM_UPGRADE_RAW_BUF_NOT_EXIST
    virtual RsvMemErrCode GetUsrData(UsrId usr, RawBuffer& usrData) = 0;
};

using RsvMemUpgradeAdaptorCreateFunc = std::function<std::unique_ptr<IRsvMemUpgradeAdaptor>()>;

// 改造现有的CReservedMemory 将其实现为 CRsvMemUpgradeAdaptor 注册给 RsvMemMng
// class CRsvMemUpgradeAdaptor : public IRsvMemUpgradeAdaptor {
// public:
//     void Initialize(const RawBuffer& rsvMem) override final;
//     bool IsRsvMemValid() override final;
//     // 通过老的sectionId 和老的 m_reservedMemOldImpl 得到每个段的保留内存数据
//     // 这个类内部维护老的 sectionId 和新的 usrId 的映射关系
//     RsvMemErrCode GetUsrData(UsrId usrId, RawBuffer& usrData) override final;

// private:
//     std::map<UsrId, uint32_t> m_usrId2SectionIdMap;
// };