//
// Created by moroz on 12.11.2020.
//

#ifndef QUIZ_FIGURE_MAP_PARSER_H
#define QUIZ_FIGURE_MAP_PARSER_H

#include "Features_lib/Objects.h"
#include <iostream>
#include <memory>
#include <boost/property_tree/ptree.hpp>
namespace pt = boost::property_tree;
#include <boost/property_tree/json_parser.hpp>
#include "Elements.h"
#include <valarray>

class Map_parser{
public:
    Map_parser(unsigned int h, unsigned int w):
    height(h), width(w){};
    ~Map_parser()= default;
    std::string create_json(std::vector<Map_object> &map) const;
private:
    unsigned int height, width;
};

#endif //QUIZ_FIGURE_MAP_PARSER_H
