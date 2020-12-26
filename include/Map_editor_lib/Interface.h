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
#include "Graphics_lib/utils.h"

#include "Graphics_lib/Shader.h"

class Interface {
public:
    Interface();
    ~Interface();
    int cycle();
    std::function<void()> draw;
    std::function<int()> processInput;
    GLFWwindow* get_window();
    void draw_menu();
    void draw_levels();
    void draw_redactor();

private:
    GLFWwindow *window;
    std::shared_ptr<Menu> menu;
    std::shared_ptr<Levels> levels;
    std::shared_ptr<Map_editor_handler> map_editor;
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

#endif //QUIZ_FIGURE_INTERFACE_H

