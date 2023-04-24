# bale kai ena cpp me ekeino to problhma poy koitoyses shmera: string trimming white space
cmake_minimum_required(VERSION 3.25)
project(benchmarking_toy_codes DESCRIPTION "Use google benchmark to measure toy codes" LANGUAGES CXX CUDA)
set(CMAKE_CXX_STANDARD 20)
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

#include(CheckLanguage)
#check_language(CUDA)
if(CMAKE_CUDA_COMPILER)
    enable_language(CUDA)
    if(NOT DEFINED CMAKE_CUDA_STANDARD)
        set(CMAKE_CUDA_STANDARD 20)
	set(CMAKE_CUDA_STANDARD_REQUIRED ON)
    endif()
    set(CMAKE_CUDA_SEPARABLE_COMPILATION ON)
    set(CMAKE_CUDA_ARCHITECTURES native)
    #CMAKE_CUDA_FLAGS to –cudart { none | shared | static }
    #set(CMAKE_CUDA_FLAGS "-Wall")

    message("[CUDA] CUDA found and will be used")
    message("[CUDA] CMAKE_CUDA_COMPILER: " ${CMAKE_CUDA_COMPILER})
    message("[CUDA] CUDA_INCLUDE_DIRS: " ${CUDA_INCLUDE_DIRS})
    message("[CUDA] CUDA_LIBRARIES: " ${CUDA_LIBRARIES})

    # ifdef USE_CUDA:
    #add_definitions(-DUSE_CUDA)

    find_package(CUDAToolkit)
    if(CUDAToolkit_FOUND)
        message("[CUDA] CUDAToolkit version " ${CUDAToolkit_VERSION} " found")
    endif()

    # CUDA helper function to convert an existing un-aliased target name's compiler options to correctly work with nvcc/native copiler
    # found on stackoverflow or here https://cliutils.gitlab.io/modern-cmake/chapters/packages/CUDA.html
    # and I liked the idea
    function(CUDA_CONVERT_FLAGS EXISTING_TARGET)
    	get_property(old_flags TARGET ${EXISTING_TARGET} PROPERTY INTERFACE_COMPILE_OPTIONS)
    	if(NOT "${old_flags}" STREQUAL "")
    	    message(WARNING "[CUDA] pre CUDA transform options: " ${old_flags})
    	    string(REPLACE ";" "," CUDA_flags "${old_flags}")
    	    set_property(TARGET ${EXISTING_TARGET} PROPERTY INTERFACE_COMPILE_OPTIONS
    	        "$<$<BUILD_INTERFACE:$<COMPILE_LANGUAGE:CXX>>:${old_flags}>$<$<BUILD_INTERFACE:$<COMPILE_LANGUAGE:CUDA>>:-Xcompiler=${CUDA_flags}>"
    	        )
    		message(WARNING "[CUDA] post CUDA transform options: " ${old_flags})
    	endif()
    endfunction()
endif()

add_subdirectory(${PROJECT_SOURCE_DIR}/src)

