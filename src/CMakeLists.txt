cmake_minimum_required(VERSION 3.25)
project(24l_zpr)

set(CMAKE_CXX_STANDARD 17)

Include(FetchContent)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.5.2)
FetchContent_GetProperties(Catch2)
FetchContent_MakeAvailable(Catch2)

add_subdirectory(test)

enable_testing()

add_executable(24l_zpr main.cpp)
