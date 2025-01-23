# find_package(Protobuf CONFIG HINTS /usr/local/Cellar/protobuf/29.1/lib/cmake/protobuf)
find_package(protobuf CONFIG REQUIRED)

set(PROTO_FILES ${CMAKE_CURRENT_SOURCE_DIR}/ModuleARsvData.proto)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/application/generated)

protobuf_generate(
    OUT_VAR PROTO_SRCS
    PROTOC_OUT_DIR ${CMAKE_BINARY_DIR}/application/generated
    LANGUAGE cpp
    PROTOS ${PROTO_FILES}
)

add_library(application_proto SHARED ${PROTO_SRCS})
# target_sources(application_proto PUBLIC ${PROTO_SRCS} ${PROTO_HDRS})
target_link_libraries(application_proto PUBLIC protobuf::libprotobuf)
