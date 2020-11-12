cmake_minimum_required(VERSION 3.1)
project(Quiz_Figure CXX C)

set(CMAKE_C_STANDARD 11)
SET(CMAKE_CXX_FLAGS "-std=c++14")

set(SOURCE_FILES src/main.cpp
        )

add_executable(Quiz_Figure src/main.cpp)

SET_TARGET_PROPERTIES(Quiz_Figure PROPERTIES LINKER_LANGUAGE C)


SET(CMAKE_C_FLAGS "-Wall -Werror -Wpedantic -fPIC")

##################### google test #####################

#------------tests def------------#


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

#------------source def------------#

include_directories("${PROJECT_SOURCE_DIR}/include")

file(GLOB sources
        "${PROJECT_SOURCE_DIR}/lib/*.c"
        "${PROJECT_SOURCE_DIR}/lib/*.h"
        "${PROJECT_SOURCE_DIR}/src/*.c")






