//
// Created by moroz on 06.12.2020.
//

#ifndef QUIZ_FIGURE_MENU_H
#define QUIZ_FIGURE_MENU_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <memory>
#include <functional>
#include <utility>
#include "Map_editor_handler.h"

#include "Elements.h"

class Menu {
public:
    Menu(GLFWwindow *window, const unsigned int &SCR_HEIGHT, const unsigned int &SCR_WIDTH);
    ~Menu(){};
    void draw_menu();
    Button_entry button_start;
    Button_entry button_map_editor;
    std::shared_ptr<Map_editor_handler> map_editor_handler;
    std::function<void()> draw;
    std::function<void()> processInput;
    void process_input();

private:
    GLFWwindow *window;
    const unsigned int SCR_HEIGHT;
    const unsigned int SCR_WIDTH;

};



#endif //QUIZ_FIGURE_MENU_H
