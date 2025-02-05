#pragma once
class ISwdlAdaptor {
public:
    virtual ~ISwdlAdaptor() = default;
    // 设备启动时 判断是不是软复位启动
    virtual bool IsSoftReset() = 0;
    // 设备启动时 判断是否正处于包加载、包匹配过程中
    virtual bool IsInSwdl() = 0;
};