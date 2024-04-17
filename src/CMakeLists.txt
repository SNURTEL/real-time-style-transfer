cmake_minimum_required(VERSION 3.25)

Include(FetchContent)

#set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
#        CACHE STRING "Vcpkg toolchain file")


set(VCPKG_MANIFEST_MODE ON)
set(CMAKE_CXX_STANDARD 20)

project(24l_zpr)

list(APPEND CMAKE_PREFIX_PATH "/home/tomek/Pobrane/libtorch")

find_package(CUDA REQUIRED)
find_package(Torch REQUIRED)

find_package(OpenCV REQUIRED)
set(OpenCV_DIR ${CMAKE_CURRENT_BINARY_DIR})
include_directories(${OpenCV_INCLUDE_DIRS})

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.5.2
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE)
FetchContent_GetProperties(Catch2)
FetchContent_MakeAvailable(Catch2)

#find_package(Catch2 REQUIRED)

add_subdirectory(test)

enable_testing()

add_executable(main main.cpp)
target_link_libraries(main "${TORCH_LIBRARIES}")
target_link_libraries(main ${OpenCV_LIBS} )
set_property(TARGET main PROPERTY CXX_STANDARD 20)
