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
    virtual UsrId GetId() = 0;
    virtual std::string_view GetName() = 0;
    // 初始化时注册到 RsvMemMng 析构时取消注册
    virtual RsvMemErrCode Initialize() = 0;
    // 从老框架升级到新框架时，根据老的解析流程恢复数据
    virtual void FrameUpgradeRecover(const uint8_t* data, size_t len) = 0;
    // RsvMemMng 任务体中遍历所有 user，如果是 dirty 的，则触发保存到保留内存
    // RsvMemMng 接收系统复位通知 复位前保存所有 dirty 的数据
    virtual RsvMemErrCode GetDataMsg(std::shared_ptr<google::protobuf::Message> dataMsg) = 0;
    // RsvMemMng 提供 Recover 接口，遍历所有的 user 调用其 Recover，操作一般在系统软复位启动初始化时发生
    virtual RsvMemErrCode Recover(const google::protobuf::Message& dataMsg) = 0;

public:
    bool m_isDirty { false };

protected: 
    // 多线程互斥操作
    mutable std::shared_mutex m_mutex;
};

using RsvMemUsrCreateFunc = std::function<std::unique_ptr<IRsvMemUsr>()>;
