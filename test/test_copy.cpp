#include <iostream>
#include <chrono>
#include <cstring>
#include <algorithm>

constexpr size_t SIZE = 60 * 1024 * 1024; // 60MB 的字节数

int main() {
    // 动态分配 60MB 模拟保留内存
    uint8_t* src = new uint8_t[SIZE];
    uint8_t* dest = new uint8_t[SIZE];
    std::fill(src, src + SIZE, 42); // 初始化源数据，填充为 42

    // 测试 memcpy
    auto start = std::chrono::high_resolution_clock::now();
    memcpy(dest, src, SIZE);
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "memcpy: " << std::chrono::duration<double, std::milli>(end - start).count() << " ms\n";

    // 测试 memmove
    start = std::chrono::high_resolution_clock::now();
    memmove(dest, src, SIZE);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "memmove: " << std::chrono::duration<double, std::milli>(end - start).count() << " ms\n";

    // 测试 std::copy
    start = std::chrono::high_resolution_clock::now();
    std::copy(src, src + SIZE, dest);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "std::copy: " << std::chrono::duration<double, std::milli>(end - start).count() << " ms\n";

    // 测试 std::copy_backward
    start = std::chrono::high_resolution_clock::now();
    std::copy_backward(src, src + SIZE, dest + SIZE);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "std::copy_backward: " << std::chrono::duration<double, std::milli>(end - start).count() << " ms\n";

    // 释放动态分配的内存
    delete[] src;
    delete[] dest;

    return 0;
}