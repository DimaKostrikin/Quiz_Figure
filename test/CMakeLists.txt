include_directories("${PROJECT_SOURCE_DIR}/include")

file(GLOB sources
        "${PROJECT_SOURCE_DIR}/src/Features_lib/*.cpp"
        )


list(REMOVE_ITEM sources "${PROJECT_SOURCE_DIR}/src/main.cpp")

file(GLOB tests "${PROJECT_SOURCE_DIR}/test/*.cpp")
list(REMOVE_ITEM tests "${PROJECT_SOURCE_DIR}/test/main_tests.cpp")

foreach(file ${tests})
    set(name)
    get_filename_component(name ${file} NAME_WE)
    add_executable("${name}_tests"
            ${sources}
            ${file}
            "${PROJECT_SOURCE_DIR}/test/main_tests.cpp")
    target_link_libraries("${name}_tests" gtest_main  gmock_main map_editor_lib physics graphics features glad ${GLFW_STATIC_LIBRARIES}
            ${FREETYPE_LIBRARIES} ${ASSIMP_LIBRARIES} ${GLM_LIBRARIES}
            ${BOOST_LIBRARIES} )
    add_test(NAME ${name} COMMAND "${name}_tests")
endforeach()