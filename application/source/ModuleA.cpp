#include "application/include/ModuleA.h"
#include "UsrHeader.pb.h"
#include <iostream>
#include <cstring>

// ModuleARsvMemUsr 实现

UsrId ModuleARsvMemUsr::GetId() {
    return 1; // 模块 A 的唯一标识符
}

std::string_view ModuleARsvMemUsr::GetName() {
    static const std::string name = "ModuleARsvMemUsr";
    return name;
}

RsvMemErrCode ModuleARsvMemUsr::Initialize() {
    std::cout << "ModuleARsvMemUsr: Initializing..." << std::endl;
    // 初始化逻辑，比如设置默认数据
    return RsvMemErrCode::RSV_MEM_SUCCESS;
}

void ModuleARsvMemUsr::FrameUpgradeRecover(const uint8_t* data, size_t len) {
    std::cout << "ModuleARsvMemUsr: Recovering frame upgrade data..." << std::endl;

    if (data == nullptr || len == 0) {
        std::cerr << "Invalid data for frame upgrade recovery." << std::endl;
        return;
    }

    // 示例：打印恢复的数据内容
    std::string recoveredData(reinterpret_cast<const char*>(data), len);
    std::cout << "Recovered data: " << recoveredData << std::endl;
}

RsvMemErrCode ModuleARsvMemUsr::GetDataMsg(std::shared_ptr<google::protobuf::Message> dataMsg)
{
    // auto msg = std::make_shared<
    // // 创建一个示例 Protobuf 消息
    // UsrHeader usrHeader;
    // usrHeader.set_usr_type(UsrType::USR_TYPE_PROTO);
    // usrHeader.set_capacity(1024); // 假设容量为 1024
    // usrHeader.set_size(512);      // 假设实际使用大小为 512
    // usrHeader.set_offset(100);    // 假设偏移量为 100

    // // 将 Protobuf 数据序列化到 dataMsg
    // if (!usrHeader.SerializeToString(dataMsg->mutable_unknown_fields())) {
    //     return RsvMemErrCode::RSV_MEM_SERIALIZATION_FAILED;
    // }

    return RsvMemErrCode::RSV_MEM_SUCCESS;
}

RsvMemErrCode ModuleARsvMemUsr::Recover(const google::protobuf::Message& dataMsg) {
    std::cout << "ModuleARsvMemUsr: Recovering from Protobuf data..." << std::endl;

    // 假设 Protobuf 消息是 UsrHeader 类型
    UsrHeader usrHeader;
    if (!usrHeader.ParseFromString(dataMsg.SerializeAsString())) {
        return RsvMemErrCode::RSV_MEM_DESERIALIZATION_FAILED;
    }

    // 打印恢复的 Protobuf 数据
    std::cout << "Recovered UsrHeader:" << std::endl;
    std::cout << " - User Type: " << usrHeader.usr_type() << std::endl;
    std::cout << " - Capacity: " << usrHeader.capacity() << std::endl;
    std::cout << " - Size: " << usrHeader.size() << std::endl;
    std::cout << " - Offset: " << usrHeader.offset() << std::endl;

    return RsvMemErrCode::RSV_MEM_SUCCESS;
}

// ModuleA 实现

void ModuleA::Initialize() {
    std::cout << "ModuleA: Initializing..." << std::endl;

    // 创建 ModuleARsvMemUsr 实例并初始化
    ModuleARsvMemUsr moduleAUsr;
    if (moduleAUsr.Initialize() != RsvMemErrCode::RSV_MEM_SUCCESS) {
        std::cerr << "ModuleA: Failed to initialize ModuleARsvMemUsr." << std::endl;
    } else {
        std::cout << "ModuleA: ModuleARsvMemUsr initialized successfully." << std::endl;
    }
}