cmake_minimum_required(VERSION 3.25)

project(common)

add_library(common
    manager.cpp
    camera.cpp
)

set_property(TARGET common PROPERTY CXX_STANDARD 20)


target_include_directories(common 
    PUBLIC 
        ${PROJECT_SOURCE_DIR}/include
)
target_link_libraries(common PRIVATE "${TORCH_LIBRARIES}")
target_link_libraries(common PRIVATE ${OpenCV_LIBS})
