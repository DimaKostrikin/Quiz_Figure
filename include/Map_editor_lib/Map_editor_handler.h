#ifndef QUIZ_FIGURE_MAP_EDITOR_HANDLER_H
#define QUIZ_FIGURE_MAP_EDITOR_HANDLER_H

#include "Scene.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "Elements.h"
#include "Parameters_label.h"
#include "Map_parser.h"


class Map_editor_handler {

public:
    Map_editor_handler();
    Map_editor_handler(GLFWwindow *window, const unsigned int &SCR_HEIGHT,
    const unsigned int &SCR_WIDTH);
    ~Map_editor_handler()=default;

    int processInput();
    void draw();
    // унести отдельно, сцену точн
    void toolbar_left_action(double &x, double &y);


private:
    GLFWwindow *window;
    Shader shader;
    void toolbar_init();
    const unsigned int SCR_HEIGHT;
    const unsigned int SCR_WIDTH;
    Map_parser parser;
    std::vector<Button_toolbar> toolbar_buttons;
    std::shared_ptr<Scene> scene;
    std::shared_ptr<Parameters_label> label;
    size_t cur_elem;
    double last_frame;
    double delta;

};


#endif //QUIZ_FIGURE_MAP_EDITOR_HANDLER_H


