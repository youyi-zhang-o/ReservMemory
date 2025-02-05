#include <gtest/gtest.h>
#include "rsv_mem_mng/include/IRsvMemMng.h"
#include "rsv_mem_mng/source/include/CRsvMemMng.h"
#include "application/include/RsvMemUpgradeAdaptor.h"
#include "application/include/ModuleA.h"
#include <vector>
#include <cstring>

class CRsvMemMngTest : public ::testing::Test {
protected:
    std::unique_ptr<IRsvMemMng> rsvMemMng {nullptr};
    std::vector<uint8_t> simulatedMemory; // 模拟的保留内存

    void SetUp() override {
        // 初始化模拟保留内存
        simulatedMemory.resize(1024); // 设置保留内存大小为 1024 字节
        std::fill(simulatedMemory.begin(), simulatedMemory.end(), 0);

        // 初始化 CRsvMemMng 对象
        rsvMemMng = RsvMemMngFactory().Create();
        rsvMemMng->Initialize(simulatedMemory.data(), simulatedMemory.size());
        std::map<UsrId, RsvMemUsrCreateFunc> createFuncMap {
            {1u, []() { return std::make_unique<ModuleARsvMemUsr>(); }}
        };
        rsvMemMng->RegUsrCreateFunc(createFuncMap);
    }

    void TearDown() override {
        // 清理操作（如果需要）
    }
};

TEST_F(CRsvMemMngTest, Initialize_ValidMemory) {
    ASSERT_TRUE(rsvMemMng->Initialize(simulatedMemory.data(), simulatedMemory.size()));
}

TEST_F(CRsvMemMngTest, Initialize_InvalidMemory) {
    ASSERT_FALSE(rsvMemMng->Initialize(nullptr, simulatedMemory.size()));
    ASSERT_FALSE(rsvMemMng->Initialize(simulatedMemory.data(), 0));
}

TEST_F(CRsvMemMngTest, Upgrade_Success) {
    auto mockUpgradeFunc = []() {
        return std::make_unique<RsvMemUpgradeAdaptor>();
    };
    rsvMemMng->RegUpgradeAdaptorCreateFunc(mockUpgradeFunc);

    ASSERT_EQ(rsvMemMng->Upgrade(), RsvMemErrCode::RSV_MEM_SUCCESS);
}

TEST_F(CRsvMemMngTest, Upgrade_Fail_NoAdaptor) {
    ASSERT_EQ(rsvMemMng->Upgrade(), RsvMemErrCode::RSV_MEM_FAILURE);
}
