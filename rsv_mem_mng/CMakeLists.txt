add_library(rsv_mem_mng SHARED)

add_subdirectory(source)
add_subdirectory(proto)

target_link_libraries(rsv_mem_mng PUBLIC rsv_mem_mng_proto)
