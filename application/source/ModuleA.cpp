#include "application/include/ModuleA.h"
#include "UsrHeader.pb.h"
#include <iostream>

std::string_view ModuleARsvMemUsr::GetName()
{
    return "ModuleARsvMemUsr";
}

RsvMemErrCode ModuleARsvMemUsr::Initialize()
{
    m_rsvMemData = std::make_shared<ModuleARsvData>();
    // 初始化逻辑，比如设置默认数据
    return RsvMemErrCode::RSV_MEM_SUCCESS;
}

void ModuleARsvMemUsr::FrameUpgradeRecover(const RawBuffer& buffer) {

}

std::shared_ptr<google::protobuf::Message> ModuleARsvMemUsr::GetDataMsg()
{
    return m_rsvMemData;
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