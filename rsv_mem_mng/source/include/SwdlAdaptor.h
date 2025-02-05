#pragma once

#include "rsv_mem_mng/include/ISwdlAdaptor.h"

class SwdlAdaptor : public ISwdlAdaptor {
public:
    SwdlAdaptor() = default;
    ~SwdlAdaptor() override = default;
    bool IsSoftReset() override { return true; }
    bool IsInSwdl() override { return false; }
};