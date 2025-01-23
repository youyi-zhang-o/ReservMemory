find_package(GTest CONFIG REQUIRED)

file(TOUCH ${CMAKE_BINARY_DIR}/dummy.cpp)
add_executable(test_exe ${CMAKE_BINARY_DIR}/dummy.cpp)
target_sources(test_exe PRIVATE test_dummy.cpp test_rsv_mem_mng.cpp)
target_link_libraries(test_exe PRIVATE GTest::gtest GTest::gtest_main rsv_mem_mng application)
