//
// Created by moroz on 12.11.2020.
//

#ifndef QUIZ_FIGURE_CONTAINER_MAP_H
#define QUIZ_FIGURE_CONTAINER_MAP_H

#include <iostream>
#include "../Objects.h"
#include <vector>
#include "memory"



class Container_map{
public:
    Container_map();
    ~Container_map();
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
};

#endif //QUIZ_FIGURE_CONTAINER_MAP_H
