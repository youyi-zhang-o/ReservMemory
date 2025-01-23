#pragma once

#include <cstddef>
#include <cstdint>

using UsrId = uint32_t;

struct RawBuffer {
    const uint8_t* data { nullptr };
    size_t len { 0 };
};

enum class RsvMemErrCode {
    RSV_MEM_SUCCESS = 0,
    RSV_MEM_FAILURE,
    RSV_MEM_UPGRADE_RAW_BUF_NOT_EXIST,
    INVALID_ARGUMENT,
    USER_ALREADY_EXISTS,
    MEMORY_NOT_ENOUGH,
    RSV_MEM_INTERNAL_ERROR,
    RSV_MEM_UPGRADE_FAILED,
    RSV_MEM_UPGRADE_ADAPTOR_NOT_FOUND,
    RSV_MEM_USER_NOT_ALLOCATED,
    RSV_MEM_DESERIALIZATION_FAILED,
};