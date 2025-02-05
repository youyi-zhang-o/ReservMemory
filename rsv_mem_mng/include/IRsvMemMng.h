#pragma once

#include <cstddef>
#include <google/protobuf/message.h>
#include <memory>
#include "IRsvMemUsr.h"
#include "pub_def.h"
#include "IRsvMemUpgradeAdaptor.h"

class IRsvMemMng {
public:
    virtual ~IRsvMemMng() = default;
    // 恢复数据或清空保留内存 在所有 usr 注册完后调用
    virtual bool Initialize(uint8_t* base, size_t size) = 0;
    virtual void RegUpgradeAdaptorCreateFunc(RsvMemUpgradeAdaptorCreateFunc&&) = 0;
    virtual RsvMemErrCode RegUsrCreateFunc(const std::map<UsrId, RsvMemUsrCreateFunc>& createFuncMap) = 0;
    virtual std::shared_ptr<IRsvMemUsr> GetUsr(UsrId id) = 0;
    // 确保所有需要升级的 User 注册完之后调用 调用这个接口之后 保留内存空间将被新框架接管
    // 对于没有历史遗留问题的新开发设备 初始化时调用 UpgradeAdator 判断保留内存无效后 直接开始使用保留内存 可以不必调用这个接口
    virtual RsvMemErrCode Upgrade() = 0;
    // 包加载、包匹配结束时通知保留内存管理模块 设备启动时判断是否处于包加载状态
    // 如果是包加载激活启动 对保留内存的写操作将被缓存
    // 等到通知包加载结束后放开对保留内存的写操作 将之前所有缓存的内容刷新到保留内存
    virtual void NotifySwdlEnd() = 0;
    // 系统关闭通知 如主动复位 单板对象析构 异常复位等；将触发将脏数据写到保留内存
    virtual void OnSystemClose() = 0;
};

/*
对于使用原始指针直接写入，且无法切换至 protobuf 的场景（多见于分配一片保留内存给其它领域使用，由其它领域自己管理）
本框架不提供管理功能。
在框架切换时，按照以下思路进行处理：
1. 推动其它领域进行整改
2. 如果剩余的保留内存空间足够，在初始化时，在使用保留内存之前，在保留内存的尾巴上分配新的空间，
把之前使用的保留内存复制一份到尾巴上，后续如果升级成功，则之前的保留内存会被框架回收，后续都使用新分配的空间。
如果升级回滚，则回滚到老版本的代码，继续使用之前的空间。在框架的 Initilize 接口调用时，传递给框架的 len 应该除去
尾巴上分配出来用于自己管理的空间
*/
class RsvMemMngFactory {
public:
    std::unique_ptr<IRsvMemMng> Create();
};