cmake_minimum_required(VERSION 3.25)

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/../vcpkg/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "Vcpkg toolchain file")


set(VCPKG_MANIFEST_MODE ON)
set(CMAKE_FIND_DEBUG_MODE 1)
set(CMAKE_CXX_STANDARD 20)

project(24l_zpr)

find_package(CUDA REQUIRED)
#find_package(OpenCV CONFIG REQUIRED)
find_package(Catch2 CONFIG REQUIRED)
#find_package(Torch REQUIRED)

#Include(FetchContent)
#
#FetchContent_Declare(
#        Torch
#        URL https://download.pytorch.org/libtorch/cu121/libtorch-cxx11-abi-shared-with-deps-2.2.2%2Bcu121.zip
#)
#FetchContent_GetProperties(Torch)
#FetchContent_MakeAvailable(Torch)
#list(APPEND CMAKE_PREFIX_PATH "${torch_SOURCE_DIR}")
#
#FetchContent_Declare(
#        Catch2
#        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
#        GIT_TAG v3.5.2
#        GIT_SHALLOW TRUE
#        GIT_PROGRESS TRUE)
#FetchContent_GetProperties(Catch2)
#FetchContent_MakeAvailable(Catch2)

# TODO OpenCV
#FetchContent_Declare(
#        OpenCV
#        GIT_REPOSITORY https://github.com/opencv/opencv.git
#        GIT_TAG        4.4.0
#        GIT_SHALLOW TRUE
#        GIT_PROGRESS TRUE
#)
#FetchContent_GetProperties(opencv)
#if (NOT opencv_POPULATED)
#    FetchContent_Populate(opencv)
#endif ()
#FetchContent_MakeAvailable(opencv)

#set(OpenCV_DIR ${CMAKE_CURRENT_BINARY_DIR})
#include_directories(${OpenCV_INCLUDE_DIRS})
#find_package(OpenCV REQUIRED)


#find_package(Torch REQUIRED)
#INCLUDE_DIRECTORIES( ${OpenCV_INCLUDE_DIRS} )

add_subdirectory(test)

enable_testing()

add_executable(main main.cpp)
#target_link_libraries(main "${TORCH_LIBRARIES}")
#target_link_libraries(main ${OpenCV_LIBS} )
set_property(TARGET main PROPERTY CXX_STANDARD 20)
