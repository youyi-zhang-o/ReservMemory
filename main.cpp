#include <iostream>
#include <vector>
#include <google/protobuf/stubs/common.h>

#include "IDeviceUpgradeStatus.h"
#include "DeviceUpgradeStatus.h"
#include "ReserveMemoryManager.h"

// 假设你有一个 .proto 文件 user_settings_data.proto
// 并用 protoc 生成了 user_settings_data.pb.h / .cc
#include "user_settings_data.pb.h"

// 模拟保留内存
static uint8_t g_reserveMem[1024 * 256]; // 256KB

int main() {
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    // 1. 初始化保留内存管理器
    auto& manager = ReserveMemoryManager::Instance();
    if (!manager.Initialize(g_reserveMem, sizeof(g_reserveMem))) {
        std::cerr << "[main] ReserveMemoryManager init failed.\n";
        return 1;
    }

    // 2. 创建一个设备升级状态对象 + 将其传给 manager
    DeviceUpgradeStatus upgradeStatus;
    manager.SetUpgradeStatusChecker(&upgradeStatus);

    // 3. 正常模式 (未升级) 写Protobuf
    {
        user::UserSettingsData msg;
        msg.set_username("Alice");
        msg.set_volume(20);

        if (!manager.SaveData(10, msg)) {
            std::cerr << "[main] SaveData(10) fail.\n";
        }
    }
    // 读取验证
    {
        user::UserSettingsData loaded;
        if (manager.LoadData(10, loaded)) {
            std::cout << "[main] Normal mode loaded => user=" << loaded.username()
                      << ", volume=" << loaded.volume() << "\n";
        }
    }

    // 4. 进入升级模式
    upgradeStatus.SetUpgrading(true);
    std::cout << "[main] Now upgrading... any SaveData goes to cache.\n";

    // 写 configId=10, 覆盖成 "Bob/99"
    {
        user::UserSettingsData msg;
        msg.set_username("Bob");
        msg.set_volume(99);
        manager.SaveData(10, msg); // 缓存
    }
    // 写一些原始字节
    {
        std::vector<uint8_t> rawData = {1,2,3,4,5};
        manager.SaveData(20, rawData); // 缓存
    }

    // 5. 升级成功 => FinishUpgrade => 一次性写入
    std::cout << "[main] FinishUpgrade => flush cached writes.\n";
    manager.FinishUpgrade();
    upgradeStatus.SetUpgrading(false);

    // 验证
    {
        user::UserSettingsData loaded;
        if (manager.LoadData(10, loaded)) {
            std::cout << "[main] After flush => user=" 
                      << loaded.username() << ", volume=" 
                      << loaded.volume() << "\n";
        }
        std::vector<uint8_t> vect;
        if (manager.LoadData(20, vect)) {
            std::cout << "[main] configId=20 => vector size=" 
                      << vect.size() << "\n";
        }
    }

    // 6. 再次升级，但最终失败 => Cancel
    upgradeStatus.SetUpgrading(true);
    {
        // 写 "Charlie/100"
        user::UserSettingsData msg;
        msg.set_username("Charlie");
        msg.set_volume(100);
        manager.SaveData(10, msg); // 缓存
    }

    std::cout << "[main] CancelUpgrade => discard cached writes.\n";
    manager.CancelUpgrade();
    upgradeStatus.SetUpgrading(false);

    // 验证(仍是Bob/99)
    {
        user::UserSettingsData loaded;
        if (manager.LoadData(10, loaded)) {
            std::cout << "[main] After cancel => user="
                      << loaded.username() << ", volume="
                      << loaded.volume() << "\n";
        }
    }

    google::protobuf::ShutdownProtobufLibrary();
    return 0;
}