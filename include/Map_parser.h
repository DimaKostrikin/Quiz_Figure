//
// Created by moroz on 12.11.2020.
//

#ifndef QUIZ_FIGURE_MAP_PARSER_H
#define QUIZ_FIGURE_MAP_PARSER_H

#include "../Objects.h"
#include <iostream>
#include <memory>
#include <boost/property_tree/ptree.hpp>
namespace pt = boost::property_tree;
#include <boost/property_tree/json_parser.hpp>
#include "GUI.h"

class Map_parser{
public:
    Map_parser(){};
    ~Map_parser(){};
    std::string create_json(); //std::vector<Map_object> map
private:
    bool parser(std::shared_ptr<Map_object> map, std::string file_name);
};

#endif //QUIZ_FIGURE_MAP_PARSER_H
