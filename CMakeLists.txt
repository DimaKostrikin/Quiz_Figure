cmake_minimum_required(VERSION 3.3)

set(LIB_NAME features_project)
set(CMAKE_CXX_STANDARD 17)

project(Features)

set(COMPILE_FLAGS -Wall -Werror -Wpedantic)

include_directories("${PROJECT_SOURCE_DIR}/include")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}")

include(CTest)

file(GLOB features_sources
        "${PROJECT_SOURCE_DIR}/include/features/*.h"
        "${PROJECT_SOURCE_DIR}/src/features/*.cpp"
        "${PROJECT_SOURCE_DIR}/test/*.test")

### GTEST
configure_file(CMakeLists.txt.in
        googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download)
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download)

add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
        ${CMAKE_BINARY_DIR}/googletest-build)
###
enable_testing()
add_subdirectory(test)

add_library(${LIB_NAME} SHARED ${features_sources})