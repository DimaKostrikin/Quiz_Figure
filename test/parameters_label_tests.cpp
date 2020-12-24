//
// Created by moroz on 24.12.2020.
//


#include "gtest/gtest.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Map_editor_lib/Parameters_label.h>

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

    Parameters_label label(h, h);
    std::shared_ptr<Map_object> mo = std::make_shared<Map_object>("../textures/cube.png", "../textures/cube_act.png", vertices,
                                                                  CUBE, 1, h, h);
    //label.draw();
    //label.set_object(mo);
    //label.draw();
    //ASSERT_EQ(label.get_object(), mo);


}