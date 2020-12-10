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
        src/GUI.cpp
        stb_image.cpp
        src/Menu.cpp
        src/Scene.cpp
        src/Container_map.cpp
        src/Parameters_label.cpp
        src/Map_parser.cpp)

#src/Container_map.cpp
#src/glad.c src/Map_parser.cpp src/Parameters_label.cpp src/Scene.cpp
#src/Map_editor_handler.cpp

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
#add_executable(Object Objects.cpp)

#add_executable(Shader shader_s.h)
#SET_TARGET_PROPERTIES(Shader PROPERTIES LINKER_LANGUAGE C)



SET_TARGET_PROPERTIES(Quiz_Figure PROPERTIES LINKER_LANGUAGE C)

SET(CMAKE_C_FLAGS " -pthread  -Wall -Werror  -fPIC ")
#SET(CMAKE_C_FLAGS " -pthread -lX11  -lXrandr -lXi -ldl  -lglfw3    ")
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

find_package(Freetype REQUIRED)

find_package(ASSIMP REQUIRED)

find_package(glm REQUIRED)

find_package(Boost REQUIRED)

TARGET_LINK_LIBRARIES(${PROJECT_NAME} PUBLIC glad ${GLFW_STATIC_LIBRARIES}
        ${FREETYPE_LIBRARIES} ${ASSIMP_LIBRARIES} ${GLM_LIBRARIES}
        ${BOOST_LIBRARIES})

INCLUDE_DIRECTORIES(${GLFW_INCLUDE_DIRS} ${FREETYPE_INCLUDE_DIRS}
        ${ASSIMP_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS} ${BOOST_INCLUDE_DIRS})


####################

add_library(map_editor_lib STATIC src/Interface.cpp include/Interface.h
        src/Map_editor_handler.cpp include/Map_editor_handler.h
        src/GUI.cpp include/GUI.h
        src/Menu.cpp include/Menu.h
        src/Scene.cpp include/Scene.h
        src/Container_map.cpp include/Container_map.h
        src/Parameters_label.cpp include/Parameters_label.h
        src/Map_parser.cpp include/Map_parser.h)

target_link_libraries(${PROJECT_NAME} PRIVATE map_editor_lib)


