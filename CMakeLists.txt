#bale edo na kanei build me ekeino to benchmark (google nomizo?)
#kai bale kai ena cpp me ekeino to problhma poy koitoyses shmera: string trimming white space
cmake_minimum_required(VERSION 3.14)
project(benchmarking_toy_codes DESCRIPTION "Use google benchmark to measure toy codes" LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

# Location of additional cmake modules
#NIKOS set(CMAKE_MODULE_PATH
#NIKOS     ${CMAKE_MODULE_PATH}
#NIKOS     ${PROJECT_SOURCE_DIR}/cmake
#NIKOS )

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

#NIKOS TODO: μηπως να το δοκίμαζα και με το git submodules όπως λέει εδώ:
#NIKOS    https://cliutils.gitlab.io/modern-cmake/chapters/projects/submodule.html
#NIKOS kati san auto edo dld:
#NIKOS git submodule add ../../owner/repo.git extern/repo
#NIKOS find_package(Git QUIET)
#NIKOS if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
#NIKOS 	# Update submodules as needed
#NIKOS 	option(GIT_SUBMODULE "Check submodules during build" ON)
#NIKOS 	if(GIT_SUBMODULE)
#NIKOS 		message(STATUS "Submodule update")
#NIKOS 		execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
#NIKOS 			WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
#NIKOS 			RESULT_VARIABLE GIT_SUBMOD_RESULT)
#NIKOS 		if(NOT GIT_SUBMOD_RESULT EQUAL "0")
#NIKOS 			message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
#NIKOS 		endif()
#NIKOS 	endif()
#NIKOS endif()
#NIKOS
#NIKOS if(NOT EXISTS "${PROJECT_SOURCE_DIR}/extern/repo/CMakeLists.txt")
#NIKOS 	message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
#NIKOS endif()

# If you want to self-test benchmark lib too, turn me ON
set(BENCHMARK_ENABLE_TESTING OFF)
include(FetchContent)
FetchContent_Declare(
	googlebenchmark
	GIT_REPOSITORY https://github.com/google/benchmark
	#GIT_TAG        release-1.8.0
	)
FetchContent_MakeAvailable(googlebenchmark)
#cmake<3.14 FetchContent_GetProperties(googlebenchmark)
#cmake<3.14 if(NOT googlebenchmark_POPULATED)
#cmake<3.14 	FetchContent_Populate(googlebenchmark)
#cmake<3.14 	add_subdirectory(${googlebenchmark_SOURCE_DIR} ${googlebenchmark_BINARY_DIR})
#cmake<3.14 endif()


find_package(Boost REQUIRED)
find_package(Eigen3 REQUIRED NO_MODULE)
find_package(OpenMP REQUIRED)

add_subdirectory(${PROJECT_SOURCE_DIR}/src)

