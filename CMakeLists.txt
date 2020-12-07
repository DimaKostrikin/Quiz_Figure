cmake_minimum_required(VERSION 3.1)
project(Quiz_Figure CXX C)

set(PROJECT_NAME Quiz_Figure)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)


set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)

#add_executable(Objects Objects.cpp)

include_directories(${INCLUDE_DIR})
include_directories(${SOURCE_DIR})



set(SOURCE_FILES src/main.cpp
        src/Interface.cpp
        src/Map_editor_handler.cpp
        src/Button_entry.cpp
        stb_image.cpp
        src/Menu.cpp)

#src/Container_map.cpp
#src/glad.c src/Map_parser.cpp src/Parameters_label.cpp src/Scene.cpp
#src/Map_editor_handler.cpp

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
#add_executable(Object Objects.cpp)

#add_executable(Shader shader_s.h)
#SET_TARGET_PROPERTIES(Shader PROPERTIES LINKER_LANGUAGE C)



SET_TARGET_PROPERTIES(Quiz_Figure PROPERTIES LINKER_LANGUAGE C)

SET(CMAKE_C_FLAGS " -pthread  -Wall -Werror  -fPIC ")
# SET(CMAKE_CXX_FLAGS "-lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl")
# SET(CMAKE_C_FLAGS "-Wall -Werror -Wpedantic -fPIC")

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

file(GLOB sources
        "${PROJECT_SOURCE_DIR}/lib/*.c"
        "${PROJECT_SOURCE_DIR}/lib/*.h"
        "${PROJECT_SOURCE_DIR}/src/*.c")


###########################



###########################

#for glad
add_library(glad "${INCLUDE_DIR}/glad/glad.h" "${SOURCE_DIR}/glad.c")
target_include_directories(glad PUBLIC ${INCLUDE_DIR})

#for glfw:
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
INCLUDE_DIRECTORIES(${GLFW_INCLUDE_DIRS})

TARGET_LINK_LIBRARIES(${PROJECT_NAME} PUBLIC glad ${GLFW_STATIC_LIBRARIES})




####################

add_library(map_editor_lib STATIC src/Interface.cpp include/Interface.h
        src/Map_editor_handler.cpp include/Map_editor_handler.h
        src/Button_entry.cpp include/Button_entry.h
        src/Menu.cpp include/Menu.h )

target_link_libraries(${PROJECT_NAME} PRIVATE map_editor_lib)