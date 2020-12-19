#ifndef LEVELS_H
#define LEVELS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <memory>
#include <functional>
#include <utility>
#include <list>
#include "Map_editor_handler.h"

#include "GUI.h"

struct State_keys {
    bool State_D = false;
    bool State_A = false;
};


class Levels {
public:
    Levels(GLFWwindow *window);
    ~Levels(){};

    std::function<void()> draw;
    std::function<int()> processInput;
    int process_input();
    void draw_levels();
    int num_of_level;
private:
    GLFWwindow *window;
    std::vector<Button_entry> buttons_levels;
    std::vector<Button_entry>::iterator it_lvl;
    State_keys state_keys;
};


#endif  // LEVELS_H
