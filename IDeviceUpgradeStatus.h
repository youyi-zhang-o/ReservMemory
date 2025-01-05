#pragma once

/**
 * @brief 设备升级状态接口：用于判断当前系统是否正处于升级中
 */
class IDeviceUpgradeStatus {
public:
    virtual ~IDeviceUpgradeStatus() = default;

    /**
     * @brief 返回当前是否正在升级中
     */
    virtual bool IsUpgrading() const = 0;
};