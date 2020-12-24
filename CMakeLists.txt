cmake_minimum_required(VERSION 3.1)

project(physics_interface)

set(CMAKE_CXX_STANDARD 11)

configure_file(CMakeLists.txt.in
        googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )

add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
        ${CMAKE_BINARY_DIR}/googletest-build)

enable_testing()
add_subdirectory(test)

include_directories("${PROJECT_SOURCE_DIR}/include")

file(GLOB sources
  "${PROJECT_SOURCE_DIR}/include/physics_interface/*.h"
  "${PROJECT_SOURCE_DIR}/src/*.cpp")

add_library(physics_interface SHARED ${sources} src/Classes.cpp include/physics_interface/classes.h)
