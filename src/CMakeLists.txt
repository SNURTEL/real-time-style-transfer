cmake_minimum_required(VERSION 3.25)
project(24l_zpr)

set(CMAKE_CXX_STANDARD 20)

Include(FetchContent)
#
#FetchContent_Declare(
#        Torch
#        URL https://download.pytorch.org/libtorch/cu121/libtorch-cxx11-abi-shared-with-deps-2.2.2%2Bcu121.zip
#)
#FetchContent_GetProperties(Torch)
#FetchContent_MakeAvailable(Torch)
#list(APPEND CMAKE_PREFIX_PATH "${torch_SOURCE_DIR}")

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.5.2)
FetchContent_GetProperties(Catch2)
FetchContent_MakeAvailable(Catch2)

#include(FetchContent)
#FetchContent_Declare(
#        opencv
#        GIT_REPOSITORY https://github.com/opencv/opencv.git
#        GIT_TAG 4.9.0
#        GIT_SHALLOW TRUE
#        GIT_PROGRESS TRUE
#        CONFIGURE_COMMAND cmake -G "Ninja"
#        -DCMAKE_INSTALL_PREFIX=${OpenCV_INSTALL_DIR}
#        -DBUILD_TESTS=OFF
#        -DBUILD_PERF_TESTS=OFF
#        -DBUILD_EXAMPLES=OFF
#        -DBUILD_opencv_apps=OFF
#        -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
#        -DWITH_ADE=OFF
#        -Wno-dev
#        -S ${CMAKE_CURRENT_SOURCE_DIR}/build/_deps/opencv-src
#        -B ${CMAKE_CURRENT_SOURCE_DIR}/build
#        BUILD_COMMAND  cmake --build . --target install WORKING_DIRECTORY ${OpenCV_BUILD_DIR}
#)
#FetchContent_MakeAvailable(opencv)


find_package(Torch REQUIRED)
find_package(OpenCV REQUIRED)

add_subdirectory(test)

enable_testing()

add_executable(24l_zpr main.cpp)
