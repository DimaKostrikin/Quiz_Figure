//
// Created by moroz on 12.11.2020.
//

#ifndef QUIZ_FIGURE_SCENE_H
#define QUIZ_FIGURE_SCENE_H

#include "../Objects.h"
#include <iostream>
#include "memory"
#include "Elements.h"


class Scene{
public:
    Scene(std::vector<float>vertices);
    Scene()=default;
    bool connection_mode;

    size_t id;
    ~Scene()= default;
    void draw();
    std::vector<Map_object> container;
    size_t cur_elem;
    void delete_elem();
    Elem paper;

    void scene_action(double &x, double &y);

    std::vector<float> vertices_paper;

private:
    void paper_maker();
    void connect(size_t &i, size_t &j);
    size_t n; //считать
    size_t save; //хелпа

};

#endif //QUIZ_FIGURE_SCENE_H
