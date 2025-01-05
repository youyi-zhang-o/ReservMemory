#pragma once
#include "IDeviceUpgradeStatus.h"

/**
 * @brief 一个简单的实现类，用于维护“是否处于升级中”的标记
 */
class DeviceUpgradeStatus : public IDeviceUpgradeStatus {
public:
    DeviceUpgradeStatus() : m_upgrading(false) {}

    /**
     * @brief 设置升级状态
     */
    void SetUpgrading(bool u) { m_upgrading = u; }

    /**
     * @brief 查询是否升级中
     */
    bool IsUpgrading() const override { return m_upgrading; }

private:
    bool m_upgrading;
};