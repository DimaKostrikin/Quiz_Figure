cmake_minimum_required(VERSION 3.15)
set(PROJECT_NAME Project_Quiz_Figure)
project(Project_Quiz_Figure)

set(CMAKE_CXX_STANDARD 17)

set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)

#file(GLOB_RECURSE SOURCE_FILES RELATIVE ${PROJECT_SOURCE_DIR} "/*.cpp")


include_directories(${INCLUDE_DIR}/graphics)
set(SOURCE_FILES src/graphics/stb_image.cpp src/graphics/Model_class.cpp src/graphics/Mesh_class.cpp src/graphics/Camera_class.cpp src/graphics/Shader.cpp src/graphics/Events_manager.cpp src/graphics/Point_light.cpp src/graphics/Render_manager.cpp src/graphics/Objects.cpp src/main.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

#add_executable(${PROJECT_NAME} ${SOURCE_DIR}/main.cpp ${SOURCE_DIR}/stb_image.cpp)

#for glad
add_library(glad "${INCLUDE_DIR}/glad/glad.h" "${SOURCE_DIR}/glad.c")
target_include_directories(glad PUBLIC ${INCLUDE_DIR})

#for glfw:
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
INCLUDE_DIRECTORIES(${GLFW_INCLUDE_DIRS})

#for assimp:
find_package(assimp 5.0.1 QUIET)

if (NOT assimp_FOUND)
    include(FetchContent)

    FetchContent_Declare(
            assimp
            URL https://github.com/assimp/assimp/archive/master.tar.gz
    )

    FetchContent_GetProperties(raylib)
    if (NOT assimp_POPULATED)
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(assimp)

        set(CMAKE_BUILD_TYPE release CACHE STRING "" FORCE)
        set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)

        add_subdirectory(${assimp_SOURCE_DIR} ${assimp_BINARY_DIR})

    endif()

endif()


#target_link_libraries(${PROJECT_NAME} assimp)


TARGET_LINK_LIBRARIES(${PROJECT_NAME} PUBLIC glad assimp ${GLFW_STATIC_LIBRARIES})