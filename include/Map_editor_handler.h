#ifndef QUIZ_FIGURE_MAP_EDITOR_HANDLER_H
#define QUIZ_FIGURE_MAP_EDITOR_HANDLER_H
//#include "Map_parser.h"
#include "Scene.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "GUI.h"
#include "Container_map.h"
#include "Parameters_label.h"
#include "Map_parser.h"


class Map_editor_handler {

public:
    size_t cur_elem;
    size_t cur_container;
    Map_editor_handler();
    Map_editor_handler(GLFWwindow *window, const unsigned int &SCR_HEIGHT,
    const unsigned int &SCR_WIDTH);
    ~Map_editor_handler();
    std::vector<Button_toolbar> toolbar_buttons;
    std::shared_ptr<Scene> scene;
    std::shared_ptr<Parameters_label> label;
    void connect(size_t i, size_t j);

    void processInput();
    std::shared_ptr<Container_map> create_map();

    float last_frame;
    float delta;

    GLFWwindow *window;
    void draw();
    // унести отдельно, сцену точн
    void toolbar_left_action(double &x, double &y);
    void scene_action(double &x, double &y);


private:
    void toolbar_init();
    void scene_init();
    const unsigned int SCR_HEIGHT;
    const unsigned int SCR_WIDTH;
    Map_parser parser;
    //std::shared_ptr<Scene>scene;
    //
    size_t n; //считать
    size_t save; //хелпа

};

/*
template<std::size_t N>
class Button_toolbar() : public Button_entry<32> {
public:
    std::string type;
    Button_toolbar(std::string name): type(name){};
};*/


#endif //QUIZ_FIGURE_MAP_EDITOR_HANDLER_H


