#ifndef KEY_PRESS_H
#define KEY_PRESS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct State_keys {
    bool State_D = false;
    bool State_A = false;
    bool State_E = false;
    bool State_S = false;
    bool State_W = false;
    bool State_Q = false;
};

bool Key_press(const int &key, GLFWwindow *window, bool &state);


#endif