//
// Created by moroz on 23.12.2020.
//

#include "gtest/gtest.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Map_editor_lib/Scene.h>

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


    Elem paper("../textures/white.png", vertices);

    // отрисовка
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO); // мы также можем генерировать несколько VAO или буферов одновременно
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    paper.draw(VAO, VBO, EBO);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    Button_entry button_start("../textures/start_text.png", "../textures/start_text_act.png", vertices);

    // смена текстур
    button_start.activate();
    ASSERT_EQ(button_start.get_texture(), button_start.get_act_texture());
    ASSERT_EQ(button_start.is_active(), true);
    button_start.deactivate();
    ASSERT_EQ(button_start.get_texture(), button_start.get_pas_texture());
    ASSERT_EQ(button_start.is_active(), false);


    Map_object mo("../textures/cube.png", "../textures/cube_act.png", vertices,
                  CUBE, 1, h, h);

    // is_вид
    ASSERT_EQ(mo.is_activator(), false);
    ASSERT_EQ(mo.is_activated(), false);
    ASSERT_EQ(mo.is_connected(), false);
    ASSERT_EQ(mo.is_static(), false);
    ASSERT_EQ(mo.is_dynamic(), true);

    // движения
    mo.up(h);
    mo.left(h);
    mo.right(h);
    mo.down(h);
    ASSERT_EQ(mo.vertices, vertices);

    // параметры
    int x = mo.x;
    float f1 = 0.8f;
    float f2 = -0.8f;
    mo.plus_width(f1, f2, f1, f2, h);
    mo.minus_width(h);
    ASSERT_EQ(mo.x, x);

    int y = mo.y;
    mo.plus_length(f1, f2, f1, f2, h);
    mo.minus_length(h);
    ASSERT_EQ(mo.y, y);

    int hh = mo.h;
    mo.plus_height();
    mo.minus_height();
    ASSERT_EQ(mo.h, hh);

    int z = mo.z;
    mo.up_z();
    mo.down_z();
    ASSERT_EQ(mo.z, z);

}