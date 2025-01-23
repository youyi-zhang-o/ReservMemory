add_library(application SHARED
    source/moduleA.cpp
    source/moduleB.cpp
)
add_subdirectory(proto)

target_include_directories(application PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(application PRIVATE rsv_mem_mng protobuf::libprotobuf)
target_link_libraries(application PUBLIC application_proto)
