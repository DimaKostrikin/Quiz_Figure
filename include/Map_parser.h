//
// Created by moroz on 12.11.2020.
//

#ifndef QUIZ_FIGURE_MAP_PARSER_H
#define QUIZ_FIGURE_MAP_PARSER_H

#include "../Objects.h"
#include <iostream>
#include <memory>
#include "Container_map.h"

class Map_parser{
public:
    Map_parser();
    ~Map_parser();
    std::string create_json(std::shared_ptr<Container_map> map);
private:
    bool parser(std::shared_ptr<Container_map> map, std::string file_name);
};

#endif //QUIZ_FIGURE_MAP_PARSER_H
