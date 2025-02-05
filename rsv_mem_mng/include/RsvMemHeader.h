#pragma once

#include <cstdint>
#include "UsrHeader.pb.h"

constexpr uint32_t RSV_MEM_MAGIC_TAG { 0x2025'55a5 };
constexpr uint32_t RSV_MEM_VER_CUR { 1 };

struct RsvMemHeader {
    // 特殊标记 判断保留内存里存储的内容是否是当前保留内存框架的数据
    uint32_t magicTag { RSV_MEM_MAGIC_TAG };
    // 保留内存框架版本号
    uint32_t ver { 0 };
    // 保留字节
    uint32_t reserved { 0 };
    // 用户头占用的空间
    uint32_t usrHeadersCapacity { 0 };
};