cmake_minimum_required(VERSION 3.10)
project(ReservedMemory)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# 设置项目根目录的包含路径
include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_BINARY_DIR})

# 添加子目录
add_subdirectory(rsv_mem_mng)
add_subdirectory(application)

# 设置主可执行文件
file(TOUCH ${CMAKE_BINARY_DIR}/dummy.cpp)
add_executable(ReservedMemory ${CMAKE_BINARY_DIR}/dummy.cpp main.cpp)

# 链接子模块库
target_link_libraries(ReservedMemory PRIVATE application rsv_mem_mng)

add_subdirectory(test)