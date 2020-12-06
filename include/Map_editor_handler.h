#ifndef QUIZ_FIGURE_MAP_EDITOR_HANDLER_H
#define QUIZ_FIGURE_MAP_EDITOR_HANDLER_H
//#include "Map_parser.h"
//#include "Scene.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>


class Map_editor_handler {

public:
    Map_editor_handler();
    Map_editor_handler(GLFWwindow *window);
    ~Map_editor_handler();

    void on_mouse_click();
    void on_key_click();

    GLFWwindow *window;
    float color;
    void draw();


private:
    void toolbar_init();
    void scene_init();
    //Map_parser parser;
    //std::shared_ptr<Scene>scene;
    //std::shared_ptr<Container_map>map;

};


#endif //QUIZ_FIGURE_MAP_EDITOR_HANDLER_H


