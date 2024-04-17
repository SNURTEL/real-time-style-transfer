cmake_minimum_required(VERSION 3.25)

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "Vcpkg toolchain file")


set(VCPKG_MANIFEST_MODE ON)
set(CMAKE_FIND_DEBUG_MODE 1)
set(CMAKE_CXX_STANDARD 20)

project(24l_zpr)

find_package(CUDA REQUIRED)
find_package(Catch2 CONFIG REQUIRED)
#find_package(Torch REQUIRED)


find_package(OpenCV CONFIG REQUIRED)
set(OpenCV_DIR ${CMAKE_CURRENT_BINARY_DIR})
include_directories(${OpenCV_INCLUDE_DIRS})


#find_package(Torch REQUIRED)

add_subdirectory(test)

enable_testing()

add_executable(main main.cpp)
#target_link_libraries(main "${TORCH_LIBRARIES}")
#target_link_libraries(main ${OpenCV_LIBS} )
set_property(TARGET main PROPERTY CXX_STANDARD 20)
