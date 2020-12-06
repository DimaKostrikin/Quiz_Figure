//
// Created by moroz on 05.12.2020.
//

#ifndef QUIZ_FIGURE_INTERFACE_H
#define QUIZ_FIGURE_INTERFACE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <memory>

// Константы
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

class Interface {
public:
    Interface();
    ~Interface();
    void cycle();
private:
    GLFWwindow *window;
    int shaderProgram;
    void processInput();
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

#endif //QUIZ_FIGURE_INTERFACE_H
