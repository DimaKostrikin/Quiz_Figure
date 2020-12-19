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
#include "Menu.h"
#include "Levels.h"

#include "Map_editor_lib/shader_s.h"


// Константы
const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 1024;


class Interface {
public:
    Interface();
    ~Interface();
    int cycle();
    std::function<void()> draw;
    std::function<int()> processInput;
    GLFWwindow* get_window();
    void draw_menu();
    void draw_leves();

private:
    GLFWwindow *window;
    int shaderProgram;
    std::shared_ptr<Menu> menu;
    std::shared_ptr<Levels> levels;
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

#endif //QUIZ_FIGURE_INTERFACE_H

