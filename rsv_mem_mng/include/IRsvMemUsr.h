#pragma once

#include <functional>
#include <memory>
#include <string_view>
#include <shared_mutex>
#include <google/protobuf/message.h>
#include "pub_def.h"

/*
是之前的业务功能类继承 IRsvMemUsr
还是新的类继承 IRsvMemUsr，将其作为业务功能类的成员？
数据与实现分离，新增类
*/
class IRsvMemUsr {
public:
    virtual ~IRsvMemUsr() = default;
    virtual std::string_view GetName() = 0;
    // 初始化时注册到 RsvMemMng 析构时取消注册
    virtual RsvMemErrCode Initialize() = 0;
    // 从老框架升级到新框架时，根据老的解析流程恢复数据
    virtual void FrameUpgradeRecover(const RawBuffer& buffer) = 0;
    // 钩子函数
    virtual void BeforeLoad() {};
    virtual void AfterLoad() {};
    virtual void BeforeSave() {};
    virtual void AfterSave() {};
    // RsvMemMng 任务体中遍历所有 user，如果是 dirty 的，则触发保存到保留内存
    // RsvMemMng 接收系统复位通知 复位前保存所有 dirty 的数据
    // 自己管理空间的用户通过查询接口得到保留内存的指针，写入通过指针完成，无需设置 dirty
    virtual std::shared_ptr<google::protobuf::Message> GetDataMsg() = 0;
    std::shared_mutex& GetSharedMutex() { return m_mutex; }

public:
    std::atomic_bool m_isDirty { false };

private:
    mutable std::shared_mutex m_mutex;
};

using RsvMemUsrCreateFunc = std::function<std::unique_ptr<IRsvMemUsr>()>;
