//
// Created by moroz on 24.12.2020.
//

#include "gtest/gtest.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Map_editor_lib/Map_editor_handler.h>

TEST(functions, ok) {
    const unsigned int h = 1280;
    glfwInit();
    // glfw: создание окна
    GLFWwindow *window = glfwCreateWindow(h, h, "FigureQuiz", nullptr, nullptr);
    if (window == nullptr){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
    }

    std::vector<float>vertices = {
            // координаты

            0.7f,  0.7f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f,   // верхняя правая
            0.7f, -0.7f, 0.0f,  1.0f, 1.0f, 1.0f,   1.0f, 0.0f,   // нижняя правая
            -0.7f, -0.7f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f,   // нижняя левая
            -0.7f, 0.7f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f
    };

    Map_editor_handler handler(window, h, h);
    //handler.processInput();
    //handler.draw();
    //double xy = 0;
    //handler.toolbar_left_action(xy, xy);



}