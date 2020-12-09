#ifndef QUIZ_FIGURE_MAP_EDITOR_HANDLER_H
#define QUIZ_FIGURE_MAP_EDITOR_HANDLER_H
//#include "Map_parser.h"
#include "Scene.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "Button_entry.h"
#include "Container_map.h"


class Map_editor_handler {

public:
    size_t cur_elem;
    size_t cur_container;
    Map_editor_handler();
    Map_editor_handler(GLFWwindow *window);
    ~Map_editor_handler();
    std::vector<Button_toolbar<32>> toolbar_buttons;
    std::shared_ptr<Scene> scene;

    void processInput();
    std::shared_ptr<Container_map> create_map();

    void on_mouse_click();
    void on_key_click();

    GLFWwindow *window;
    void draw();


private:
    void toolbar_init();
    void scene_init();
    //Map_parser parser;
    //std::shared_ptr<Scene>scene;
    //std::shared_ptr<Container_map>map;

};

/*
template<std::size_t N>
class Button_toolbar() : public Button_entry<32> {
public:
    std::string type;
    Button_toolbar(std::string name): type(name){};
};*/


#endif //QUIZ_FIGURE_MAP_EDITOR_HANDLER_H


