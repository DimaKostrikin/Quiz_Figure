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
#include "Map_editor_lib/Key_press.h"


class Menu {
public:
    Menu(GLFWwindow *window);
    ~Menu(){};
    void draw_menu();
    Button_entry button_start;
    Button_entry button_map_editor;
    std::shared_ptr<Map_editor_handler> map_editor_handler;
    std::function<void()> draw;
    std::function<int()> processInput;
    int process_input();

private:
    GLFWwindow *window;
    State_keys state_keys;
};




#endif //QUIZ_FIGURE_MENU_H
