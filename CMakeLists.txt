cmake_minimum_required(VERSION 3.15)
set(PROJECT_NAME Project_Quiz_Figure)
project(Project_Quiz_Figure)

set(CMAKE_CXX_STANDARD 17)

set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)

include_directories(${INCLUDE_DIR})
add_executable(${PROJECT_NAME} ${SOURCE_DIR}/main.cpp)

#for glad
add_library(glad "${INCLUDE_DIR}/glad/glad.h" "${SOURCE_DIR}/glad.c")
target_include_directories(glad PUBLIC ${INCLUDE_DIR})

#for glfw:
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
INCLUDE_DIRECTORIES(${GLFW_INCLUDE_DIRS})


TARGET_LINK_LIBRARIES(${PROJECT_NAME} PUBLIC glad ${GLFW_STATIC_LIBRARIES})