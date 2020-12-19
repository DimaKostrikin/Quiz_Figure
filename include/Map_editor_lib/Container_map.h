//
// Created by moroz on 12.11.2020.
//

#ifndef QUIZ_FIGURE_CONTAINER_MAP_H
#define QUIZ_FIGURE_CONTAINER_MAP_H

#include <iostream>
#include "Features_lib/Objects.h"
#include <vector>
#include "memory"
#include "Scene.h"



class Container_map{
public:
    Container_map(){cur_elem_id=0; cur_id=0;};
    Container_map(std::shared_ptr<Scene> scene);
    ~Container_map();
    size_t cur_id;
    void add_object(std::shared_ptr<Object>);
    void delete_object(std::shared_ptr<Object>);
    void change_object(std::shared_ptr<Object>);
    std::shared_ptr<Object> get_object(size_t id);

private:
    size_t cur_elem_id;
    size_t get_unique_id();
    std::vector<Object_static> static_elems;
    std::vector<Object_dynamic> dynamic_elems;
    std::vector<Object_activated> activated_elems;
    std::vector<Object_activator> activator_elems;
    std::vector<Object_influence> influence_elems;
};

#endif //QUIZ_FIGURE_CONTAINER_MAP_H
