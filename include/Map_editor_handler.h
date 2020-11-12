//
// Created by moroz on 12.11.2020.
//

#ifndef QUIZ_FIGURE_MAP_EDITOR_HANDLER_H
#define QUIZ_FIGURE_MAP_EDITOR_HANDLER_H

#include "Map_parser.h"
#include "Scene.h"

class Map_editor_handler{
public:
    Map_editor_handler();
    ~Map_editor_handler();

    void on_mouse_click();
    void on_key_click();


private:
    void toolbar_init();
    void scene_init();
    Map_parser parser;
    std::shared_ptr<Scene>scene;
    std::shared_ptr<Container_map>map;

};


#endif //QUIZ_FIGURE_MAP_EDITOR_HANDLER_H
