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
    // 为使用protobuf的用户分配内存 从前往后分 用于保留当前空闲内存首地址相当于保留内存基地址的偏移值
    uint64_t freeBegin { 0 };
    // 为使用原生内存管理策略的用户分配内存 从后往前分 大小不允许修改 用于保存当前空闲内存段最后一个字节之后一个字节相对于保留内存基地址的偏移值
    uint64_t freeEnd { 0 };
};