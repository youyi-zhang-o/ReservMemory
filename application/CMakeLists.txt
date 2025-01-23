# 创建 application 静态库
add_library(application SHARED
    source/moduleA.cpp
    source/moduleB.cpp
)
find_package(protobuf CONFIG REQUIRED)
add_subdirectory(proto)
# 设置 application 的包含路径
target_include_directories(application PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(application PRIVATE rsv_mem_mng rsv_mem_mng_proto)
target_link_libraries(application PRIVATE application_proto)
target_link_libraries(application PRIVATE protobuf::libprotobuf)
