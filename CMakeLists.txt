# bale kai ena cpp me ekeino to problhma poy koitoyses shmera: string trimming white space
cmake_minimum_required(VERSION 3.20)
project(benchmarking_toy_codes DESCRIPTION "Use google benchmark to measure toy codes" LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

# Guard against in-source builds and bad build-type strings
#include(ConfigSafeGuards)
# Adapted from: https://github.com/bast/cmake-example/tree/master/cmake
# guard against in-source builds
if(${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_BINARY_DIR})
    message(FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there.")
endif()

# guard against bad build-type strings
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

string(TOLOWER "${CMAKE_BUILD_TYPE}" cmake_build_type_tolower)
string(TOUPPER "${CMAKE_BUILD_TYPE}" cmake_build_type_toupper)
if(    NOT cmake_build_type_tolower STREQUAL "debug"
   AND NOT cmake_build_type_tolower STREQUAL "release"
   AND NOT cmake_build_type_tolower STREQUAL "profile"
   AND NOT cmake_build_type_tolower STREQUAL "relwithdebinfo")
      message(FATAL_ERROR "Unknown build type \"${CMAKE_BUILD_TYPE}\". Allowed values are Debug, Release, Profile, RelWithDebInfo (case-insensitive).")
endif()

#NIKOS include(CTest)

find_package(Boost REQUIRED)
find_package(benchmark CONFIG REQUIRED)
find_package(Eigen3 CONFIG REQUIRED)
find_package(OpenMP REQUIRED)

check_language(CUDA)
if(CMAKE_CUDA_COMPILER)
    enable_language(CUDA)

    # to tell your code it was found via #ifdef USE_CUDA:
    add_definitions(-DUSE_CUDA)

    include_directories("${CMAKE_CUDA_TOOLKIT_INCLUDE_DIRECTORIES}")
    #ADD THIS TO REQUIRED TARGETS:    set_target_properties(${PROJECT_NAME} PROPERTIES CUDA_ARCHITECTURES "35;50;72")
endif()

add_subdirectory(${PROJECT_SOURCE_DIR}/src)

