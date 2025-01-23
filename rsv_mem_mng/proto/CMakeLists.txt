set(PROTO_FILES ${CMAKE_CURRENT_SOURCE_DIR}/UsrHeader.proto)
set(PROTO_OUT_DIR ${CMAKE_BINARY_DIR}/rsv_mem_mng/generated)
file(MAKE_DIRECTORY ${PROTO_OUT_DIR})

protobuf_generate(
    OUT_VAR PROTO_SRCS
    PROTOC_OUT_DIR ${PROTO_OUT_DIR}
    LANGUAGE cpp
    PROTOS ${PROTO_FILES}
)

add_library(rsv_mem_mng_proto SHARED ${PROTO_SRCS})
target_include_directories(rsv_mem_mng_proto PUBLIC ${PROTO_OUT_DIR})
# protobuf header include by link
target_link_libraries(rsv_mem_mng_proto PRIVATE protobuf::libprotobuf)
