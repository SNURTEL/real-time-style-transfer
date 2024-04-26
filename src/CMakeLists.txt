cmake_minimum_required(VERSION 3.25)

include(FetchContent)

# [Setup/VCPKG]
if (USE_VCPKG)
    set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")
endif ()

set(VCPKG_MANIFEST_MODE ON)

# [Setup/C++]
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DDEFINED_IN_CMAKELISTS")

# [Setup/Qt]
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# [Windows]
if (WIN32)
    set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}")
    set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}")
endif ()


# [Setup/Project]
project(24l_zpr)


# [Setup/Package] CudaToolkit
if (NOT NO_USE_CUDA)
    find_package(CUDAToolkit REQUIRED)
else ()
    message("Skipping CUDA check")
endif ()

# [Setup/Package] Torch
find_package(Torch REQUIRED)

# [Setup/Package] OpenCV
find_package(OpenCV REQUIRED)
set(OpenCV_DIR ${CMAKE_CURRENT_BINARY_DIR})
include_directories(SYSTEM ${OpenCV_INCLUDE_DIRS})

# [Setup/Package] Qt6
# [Windows/Bugs] Due to bugs, variable is set directly in CMakeLists
IF (WIN32)
    set(CMAKE_PREFIX_PATH "C:/Qt/6.7.0/msvc2019_64")
ENDIF ()
find_package(Qt6 COMPONENTS Core Widgets REQUIRED)

# apt does not have QT 6.3, which introduces `qt_standard_project_setup`
if (Qt6Core_VERSION VERSION_LESS "6.3")
    message( "Qt version lower that 6.3; cannot use qt_standard_project_setup" )
    set(CMAKE_AUTOMOC ON) 
    set(CMAKE_AUTORCC ON) 
    set(CMAKE_AUTOUIC ON)
else ()
    qt_standard_project_setup()
endif ()

# [Setup/Tests] Setup tests
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.5.2
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE)
FetchContent_GetProperties(Catch2)
FetchContent_MakeAvailable(Catch2)

add_subdirectory(test)

enable_testing()


# [Project/Build] Business logic
add_library(
        model
        model/manager.hpp
        model/manager.cpp
)
target_link_libraries(model PRIVATE "${TORCH_LIBRARIES}")
target_link_libraries(model PRIVATE ${OpenCV_LIBS})
set_property(TARGET model PROPERTY CXX_STANDARD 20)

# [Project/Build] Qt Application
qt_add_executable(app MANUAL_FINALIZATION main.cpp
        main.cpp
        ui/application.hpp
        ui/application.cpp
        ui/main_window.hpp
        ui/main_window.cpp
        ui/resources.qrc
)
target_link_libraries(app PRIVATE model)
target_link_libraries(app PRIVATE Qt6::Widgets)
target_link_libraries(app PUBLIC fmt)
set_property(TARGET app PROPERTY CXX_STANDARD 20)
qt_finalize_executable(app)

# [Windows/MSVC]: Enable building Qt applications under MSVC
if (MSVC)
    target_compile_options(app PUBLIC "/Zc:__cplusplus" "/permissive-")
endif ()

# [Windows]: Copy DLLs into output directory
if (WIN32)
    add_custom_command(TARGET app POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_RUNTIME_DLLS:app> $<TARGET_FILE_DIR:app>
            COMMAND_EXPAND_LISTS
    )

    file(GLOB TORCH_DLLS "${TORCH_INSTALL_PREFIX}/lib/*.dll")
    add_custom_command(TARGET app
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${TORCH_DLLS}
            $<TARGET_FILE_DIR:app>
    )
endif ()