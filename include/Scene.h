//
// Created by moroz on 12.11.2020.
//

#ifndef QUIZ_FIGURE_SCENE_H
#define QUIZ_FIGURE_SCENE_H

#include "../Objects.h"
#include <iostream>
#include "memory"
#include "Button_entry.h"
//#include "Parameters_label.h"

class Scene{
public:
    Scene();
    ~Scene(){};
    void draw();
    std::vector<Map_object<32>> container;
    size_t cur_elem;

    void draw_object(std::shared_ptr<Object> obj);
    void change_object(std::shared_ptr<Object> obj);
    void clear_object(std::shared_ptr<Object> obj);
    void init_label();
    //std::shared_ptr<Parameters_label> label;

private:
    void grid_maker();
};

#endif //QUIZ_FIGURE_SCENE_H
