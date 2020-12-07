//
// Created by moroz on 05.12.2020.
//

#ifndef QUIZ_FIGURE_INTERFACE_H
#define QUIZ_FIGURE_INTERFACE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <memory>
#include <functional>
#include <utility>
#include "Map_editor_handler.h"
#include "Menu.h"

#include "../stb_image.h"


// Константы
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


class Interface {
public:
    Interface();
    ~Interface();
    void cycle();
    std::function<void()> draw;
    std::function<void()> processInput;
    std::shared_ptr<Menu> menu;

private:
    GLFWwindow *window;
    int shaderProgram;
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

#endif //QUIZ_FIGURE_INTERFACE_H

