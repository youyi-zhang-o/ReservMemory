#pragma once

#include "rsv_mem_mng/include/IRsvMemUsr.h"

class ModuleARsvMemUsr : public IRsvMemUsr {
public:
    ModuleARsvMemUsr() = default;
    ~ModuleARsvMemUsr() override = default;

    UsrId GetId() override final;
    std::string_view GetName() override final;
    RsvMemErrCode Initialize() override final;
    void FrameUpgradeRecover(const uint8_t* data, size_t len) override final;
    RsvMemErrCode GetDataMsg(std::shared_ptr<google::protobuf::Message> dataMsg) override final;
    RsvMemErrCode Recover(const google::protobuf::Message& dataMsg) override final;

private:
    
};

class ModuleA {
public:
    void Initialize();
};