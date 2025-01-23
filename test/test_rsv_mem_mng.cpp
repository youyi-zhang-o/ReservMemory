#include <gtest/gtest.h>
#include "rsv_mem_mng/source/include/CRsvMemMng.h"
#include "application/include/RsvMemUpgradeAdaptor.h"
#include "application/include/ModuleA.h"
#include <vector>
#include <cstring>

class CRsvMemMngTest : public ::testing::Test {
protected:
    CRsvMemMng rsvMemMng;
    std::vector<uint8_t> simulatedMemory; // 模拟的保留内存

    void SetUp() override {
        // 初始化模拟保留内存
        simulatedMemory.resize(1024); // 设置保留内存大小为 1024 字节
        std::fill(simulatedMemory.begin(), simulatedMemory.end(), 0);

        // 初始化 CRsvMemMng 对象
        rsvMemMng.Initialize(simulatedMemory.data(), simulatedMemory.size());
    }

    void TearDown() override {
        // 清理操作（如果需要）
    }
};

TEST_F(CRsvMemMngTest, Initialize_ValidMemory) {
    ASSERT_TRUE(rsvMemMng.Initialize(simulatedMemory.data(), simulatedMemory.size()));
}

TEST_F(CRsvMemMngTest, Initialize_InvalidMemory) {
    ASSERT_FALSE(rsvMemMng.Initialize(nullptr, simulatedMemory.size()));
    ASSERT_FALSE(rsvMemMng.Initialize(simulatedMemory.data(), 0));
}

TEST_F(CRsvMemMngTest, RegisterUsrCreateFunc_ValidFunc) {
    ASSERT_EQ(rsvMemMng.RegUsrCreateFunc(0, [](){return std::make_unique<ModuleARsvMemUsr>(); }),
        RsvMemErrCode::RSV_MEM_SUCCESS);
}

TEST_F(CRsvMemMngTest, RegisterUsrCreateFunc_InvalidFunc) {
    ASSERT_EQ(rsvMemMng.RegUsrCreateFunc(1, nullptr), RsvMemErrCode::INVALID_ARGUMENT);
}

TEST_F(CRsvMemMngTest, RegisterRawBufferUsr_Success) {
    auto result = rsvMemMng.RegRawBufferUsr(1, 128);
    ASSERT_EQ(result, RsvMemErrCode::RSV_MEM_SUCCESS);

    RawBuffer buffer;
    ASSERT_EQ(rsvMemMng.GetRawBuffer(1, buffer), RsvMemErrCode::RSV_MEM_SUCCESS);
    ASSERT_EQ(buffer.len, 128);
    // ASSERT_EQ(buffer.data, simulatedMemory.data() + sizeof(RsvMemHeader) + m_usrHeadersCapacity);
}

TEST_F(CRsvMemMngTest, RegisterRawBufferUsr_MemoryNotEnough) {
    auto result = rsvMemMng.RegRawBufferUsr(1, simulatedMemory.size() + 1);
    ASSERT_EQ(result, RsvMemErrCode::MEMORY_NOT_ENOUGH);
}

TEST_F(CRsvMemMngTest, RegisterRawBufferUsr_UserAlreadyExists) {
    rsvMemMng.RegRawBufferUsr(1, 128);
    auto result = rsvMemMng.RegRawBufferUsr(1, 128);
    ASSERT_EQ(result, RsvMemErrCode::USER_ALREADY_EXISTS);
}

TEST_F(CRsvMemMngTest, GetRawBuffer_Success) {
    rsvMemMng.RegRawBufferUsr(1, 128);

    RawBuffer buffer;
    ASSERT_EQ(rsvMemMng.GetRawBuffer(1, buffer), RsvMemErrCode::RSV_MEM_SUCCESS);
    ASSERT_NE(buffer.data, nullptr);
    ASSERT_EQ(buffer.len, 128);
}

TEST_F(CRsvMemMngTest, GetRawBuffer_UserNotAllocated) {
    RawBuffer buffer;
    ASSERT_EQ(rsvMemMng.GetRawBuffer(1, buffer), RsvMemErrCode::RSV_MEM_USER_NOT_ALLOCATED);
}


TEST_F(CRsvMemMngTest, Upgrade_Success) {
    auto mockUpgradeFunc = []() {
        return std::make_unique<RsvMemUpgradeAdaptor>();
    };
    rsvMemMng.RegUpgradeAdaptorCreateFunc(mockUpgradeFunc);

    ASSERT_EQ(rsvMemMng.Upgrade(), RsvMemErrCode::RSV_MEM_SUCCESS);
}

TEST_F(CRsvMemMngTest, Upgrade_Fail_NoAdaptor) {
    ASSERT_EQ(rsvMemMng.Upgrade(), RsvMemErrCode::RSV_MEM_UPGRADE_ADAPTOR_NOT_FOUND);
}