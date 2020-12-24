//
// Created by moroz on 23.12.2020.
//

#include "gtest/gtest.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Map_editor_lib/Scene.h>

TEST(functions, ok) {

    glfwInit();
    // glfw: создание окна
    GLFWwindow *window = glfwCreateWindow(800, 800, "FigureQuiz", nullptr, nullptr);
    if (window == nullptr){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
    }

    const unsigned int SCR_WIDTH = 1280;
    const unsigned int SCR_HEIGHT = 1280;

    std::vector<float>vertices = {
            // координаты

            0.7f,  0.7f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f,   // верхняя правая
            0.7f, -0.7f, 0.0f,  1.0f, 1.0f, 1.0f,   1.0f, 0.0f,   // нижняя правая
            -0.7f, -0.7f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f,   // нижняя левая
            -0.7f, 0.7f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f
    };

    Scene scene(vertices);
    scene.container.emplace_back(Map_object
            ("../textures/start.png", "../textures/start_act.png", vertices,
             START, ++scene.id, SCR_HEIGHT, SCR_WIDTH));
    scene.container.emplace_back(Map_object
                                          ("../textures/exit.png", "../textures/exit_act.png", vertices,
                                           FINISH, ++scene.id, SCR_HEIGHT, SCR_WIDTH));
    scene.container.emplace_back(Map_object
                                          ("../textures/hole.png", "../textures/hole_act.png", vertices,
                                           HOLE, ++scene.id, SCR_HEIGHT, SCR_WIDTH));
    scene.container.emplace_back(Map_object
                                          ("../textures/cube.png", "../textures/cube_act.png", vertices,
                                           CUBE, ++scene.id, SCR_HEIGHT, SCR_WIDTH));

    // соединение
    size_t i=2, j=3;
    scene.connect(i, j);
    ASSERT_EQ(scene.container[2].connect, 4);

    // удаление

    scene.container[scene.cur_elem].activate();
    scene.delete_elem();
    ASSERT_EQ(scene.container[1].connect, 0);
    ASSERT_EQ(scene.container.size(), 3);

    // отрисовка
    scene.draw();

    // погашение элементов
    scene.cur_elem = 0;
    scene.container[scene.cur_elem].activate();
    double value = 0;
    scene.scene_action(value, value, SCR_HEIGHT, SCR_WIDTH);
    ASSERT_EQ(scene.container[0].is_active(), false);

}
