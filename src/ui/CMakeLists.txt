cmake_minimum_required(VERSION 3.25)

project(ui)


# [Setup/Package] Qt6
find_package(Qt6 COMPONENTS Core Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# [Windows/Bugs] Due to bugs, variable is set directly in CMakeLists
IF (WIN32)
    set(CMAKE_PREFIX_PATH "C:/Qt/6.7.0/msvc2019_64")
ENDIF ()

# [Project/Build] Library
add_library(ui
        application.cpp
        main_window.cpp
        view.cpp
        pages/page.cpp
        pages/image_page.cpp
        pages/camera_page.cpp
        pages/models_page.cpp
        components/model_list_element.cpp
        resources.qrc
)
target_include_directories(ui
        PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

set_property(TARGET ui PROPERTY CXX_STANDARD 20)

target_link_libraries(ui PRIVATE Qt6::Widgets)

target_link_libraries(ui PRIVATE common)

# [Windows/MSVC]: Enable building Qt applications under MSVC
if (MSVC)
    target_compile_options(ui PUBLIC "/Zc:__cplusplus" "/permissive-")
endif ()