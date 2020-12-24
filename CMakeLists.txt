cmake_minimum_required(VERSION 3.1)
project(Quiz_Figure CXX C)

set(PROJECT_NAME Quiz_Figure)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)


set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}) # важная строка


include_directories(${INCLUDE_DIR})
include_directories(${SOURCE_DIR})


set(SOURCE_FILES src/main.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

SET_TARGET_PROPERTIES(Quiz_Figure PROPERTIES LINKER_LANGUAGE C)

SET(CMAKE_C_FLAGS " -pthread  -Wall -Werror  -fPIC")
SET(CMAKE_C_FLAGS " -pthread -lX11  -lXrandr -lXi -ldl  -lglfw3")
SET(CMAKE_CXX_FLAGS "-pthread -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl -fPIC")
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


#for glad
add_library(glad "${INCLUDE_DIR}/glad/glad.h" "${SOURCE_DIR}/glad.c")
target_include_directories(glad PUBLIC ${INCLUDE_DIR})

#for glfw:
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

find_package(Freetype REQUIRED)

if (assimp_FOUND)
    set(ASSIMP_LIBRARIES "assimp")
    add_library(${ASSIMP_LIBRARIES} SHARED IMPORTED)
    set_target_properties(${ASSIMP_LIBRARIES} PROPERTIES IMPORTED_LOCATION "${ASSIMP_LIBRARY_DIRS}/libassimp.so")
endif(assimp_FOUND)

find_package(ASSIMP REQUIRED)

find_package(glm REQUIRED)

find_package(Boost REQUIRED)


INCLUDE_DIRECTORIES(${GLFW_INCLUDE_DIRS} ${FREETYPE_INCLUDE_DIRS}
        ${ASSIMP_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS} ${BOOST_INCLUDE_DIRS})


####################


file(GLOB features_sources
        "include/Features_lib/*.h"
        "src/Features_lib/*.cpp")

file(GLOB map_editor_sources
        "include/Map_editor_lib/*.h"
        "src/Map_editor_lib/*.cpp")

file(GLOB physics_sources
        "include/Physics_lib/*.h"
        "src/Physics_lib/*.cpp")

file(GLOB graphics_sources
        "include/Graphics_lib/*.h"
        "src/Graphics_lib/*.cpp")

add_library(map_editor_lib STATIC ${map_editor_sources})

target_link_libraries(map_editor_lib glad ${GLFW_STATIC_LIBRARIES}
        ${FREETYPE_LIBRARIES} ${ASSIMP_LIBRARIES} ${GLM_LIBRARIES}
        ${BOOST_LIBRARIES})

add_library(features STATIC ${features_sources})

add_library(graphics STATIC ${graphics_sources})

target_link_libraries(graphics glad ${GLFW_STATIC_LIBRARIES}
        ${FREETYPE_LIBRARIES} ${ASSIMP_LIBRARIES} ${GLM_LIBRARIES}
        ${BOOST_LIBRARIES})

target_link_libraries(features PUBLIC map_editor_lib graphics)

add_library(physics STATIC ${physics_sources})

target_link_libraries(physics ${GLFW_STATIC_LIBRARIES}
        ${FREETYPE_LIBRARIES} ${ASSIMP_LIBRARIES} ${GLM_LIBRARIES}
        ${BOOST_LIBRARIES})


target_link_libraries(${PROJECT_NAME} PUBLIC features physics)

