//
// Created by moroz on 12.11.2020.
//

#ifndef QUIZ_FIGURE_SCENE_H
#define QUIZ_FIGURE_SCENE_H

#include "Object.h"
#include <iostream>
#include "memory"
#include "Parameters_label.h"

class Scene{
public:
    Scene();
    ~Scene();
    void draw_object(std::shared_ptr<Object> obj);
    void change_object(std::shared_ptr<Object> obj);
    void clear_object(std::shared_ptr<Object> obj);
    void init_label();
private:
    void grid_maker();
    std::shared_ptr<Parameters_label> label;
};

#endif //QUIZ_FIGURE_SCENE_H
