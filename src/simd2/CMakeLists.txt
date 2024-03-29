#set(CMAKE_TOOLCHAIN_FILE "D:\vcpkg\scripts\buildsystems\vcpkg.cmake")

cmake_minimum_required(VERSION 3.21)
project(benchmarks)

set(CXX_STANDARD 20)
set(CXX_STANDARD_REQUIRED ON)
set(CXX_EXTENSIONS ON)

#add_executable(gcc_pragma_avx2 gcc_pragma_avx2.cpp)
add_executable(intrinsics intrinsics.cpp)
#add_executable(aligned_load aligned_load.cpp)
#set_property(TARGET target PROPERTY CXX_STANDARD 20)
