#pragma once

#include "rsv_mem_mng/include/IRsvMemUsr.h"
#include <application/generated/ModuleARsvData.pb.h>

class ModuleARsvMemUsr : public IRsvMemUsr {
public:
    ModuleARsvMemUsr() = default;
    ~ModuleARsvMemUsr() override = default;
    std::string_view GetName() override final;
    RsvMemErrCode Initialize() override final;
    void FrameUpgradeRecover(const RawBuffer& buffer) override final;
    std::shared_ptr<google::protobuf::Message> GetDataMsg() override final;

private:
    std::shared_ptr<google::protobuf::Message> m_rsvMemData {nullptr};
};

class ModuleA {
public:
    void Initialize();
};