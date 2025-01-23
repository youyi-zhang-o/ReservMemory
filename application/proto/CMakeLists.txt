set(PROTO_FILES ${CMAKE_CURRENT_SOURCE_DIR}/ModuleARsvData.proto)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/application/generated)

protobuf_generate(
    OUT_VAR PROTO_SRCS
    PROTOC_OUT_DIR ${CMAKE_BINARY_DIR}/application/generated
    LANGUAGE cpp
    PROTOS ${PROTO_FILES}
)

add_library(application_proto SHARED ${PROTO_SRCS})
target_link_libraries(application_proto PRIVATE protobuf::libprotobuf)
