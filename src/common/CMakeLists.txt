cmake_minimum_required(VERSION 3.25)

project(common)
include(CMakePrintHelpers)
find_package(Python REQUIRED COMPONENTS Interpreter Development)

set(BOOST_INCLUDE_LIBRARIES python)
set(BOOST_ENABLE_CMAKE ON)
include(FetchContent)
FetchContent_Declare(
  Boost
  GIT_REPOSITORY https://github.com/boostorg/boost.git
  GIT_TAG boost-1.85.0
  GIT_SUBMODULES libs/python
  GIT_SHALLOW TRUE
)
FetchContent_GetProperties(Boost)
FetchContent_Populate(Boost)
FetchContent_MakeAvailable(Boost)

add_library(common
    model.cpp
    camera.cpp
    utils.cpp
    model_manager.cpp
)
set_property(TARGET common PROPERTY CXX_STANDARD 20)
target_include_directories(common 
    PUBLIC 
        ${PROJECT_SOURCE_DIR}/include
)
find_package(Python COMPONENTS Interpreter Development REQUIRED)
# include_directories(${PYTHON_INCLUDE_DIRS})



IF(PYTHON_VERSION)
    cmake_print_variables(PYTHON_VERSION)
    find_package(Boost COMPONENTS ${PYTHON_VERSION} REQUIRED)
ELSE()
    message("PYTHON_VERSION not defined, searching automatically")
    
    find_package(Boost COMPONENTS python312)

    IF(NOT Boost_python312_FOUND)
        find_package(Boost COMPONENTS python311)
    ENDIF()
    IF(NOT Boost_python311_FOUND AND NOT Boost_python312_FOUND)
        find_package(Boost COMPONENTS python310)
    ENDIF()
    IF(NOT Boost_python310_FOUND AND NOT Boost_python311_FOUND AND NOT Boost_python312_FOUND)
        find_package(Boost COMPONENTS python39)
    ENDIF()
    IF(NOT Boost_python39_FOUND AND NOT Boost_python310_FOUND AND NOT Boost_python311_FOUND AND NOT Boost_python312_FOUND) 
        message( FATAL_ERROR "Could not find Boost::python for any version 3.9-3.12" )
    ENDIF()

    cmake_print_variables(Boost_python312_FOUND Boost_python311_FOUND Boost_python310_FOUND Boost_python39_FOUND)
ENDIF()

INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )


target_link_libraries(common PRIVATE "${TORCH_LIBRARIES}")
target_link_libraries(common PRIVATE ${OpenCV_LIBS})
target_link_libraries(common PRIVATE ${Boost_LIBRARIES} Python::Python)
