#include "Features_lib/Parser.h"
#include <iostream>
#include <boost/foreach.hpp>

void print(boost::property_tree::ptree const& pt)
{
    using boost::property_tree::ptree;
    ptree::const_iterator end = pt.end();
    for (ptree::const_iterator it = pt.begin(); it != end; ++it)
    {
        std::cout << it->first << ": " << it->second.get_value<std::string>() << std::endl;
        print(it->second);
    }
}



Parser::Parser(std::list<Object_dynamic> &obj_dyn,
               std::list<Object_static> &obj_stat,
               std::list<Object_activated> &obj_acted,
               std::list<Object_activator> &obj_actor,
               std::list<Object_influence> &obj_infl)
               : obj_dyn(obj_dyn),
               obj_stat(obj_stat),
               obj_acted(obj_acted),
               obj_actor(obj_actor),
               obj_infl(obj_infl) {}

void Parser::fill_from(std::string path_to_json) {
    boost::property_tree::read_json(path_to_json, pt_json);
    boost::property_tree::ptree::const_iterator end = pt_json.end();

    clear_lists();

    fill_static("walls");
    fill_static("cubes");

}

int Parser::get_elem_enum(const std::string &elem_type) {
    int elem_enum = WALL;

    if (elem_type == "walls")
        elem_enum = WALL;

    if (elem_type == "platform")
        elem_enum = PLATFORM;

    if (elem_type == "stairs")
        elem_enum = STAIRS;

    if (elem_type == "player")
        elem_enum = PLAYER;

    if (elem_type == "cubes")
        elem_enum = CUBE;

    if (elem_type == "balls")
        elem_enum = BALL;

    if (elem_type == "doors")
        elem_enum = DOOR;

    if (elem_type == "buttons")
        elem_enum = BUTTON;

    if (elem_type == "steps")
        elem_enum = STEP;

    if (elem_type == "holes")
        elem_enum = HOLE;

    return elem_enum;
}

void Parser::clear_lists() {
    obj_stat.clear();
    obj_dyn.clear();
    obj_infl.clear();
    obj_actor.clear();
    obj_acted.clear();
}

void Parser::fill_static(const std::string &elem_type) {
    Point p;
    Size sz;
    for (auto &wall : pt_json.get_child(elem_type)) {
        for (auto &con : wall.second.get_child("")) {
            std::cout << con.first << ": " << con.second.data() << std::endl;
            if (con.first == "x")
                p.x = con.second.get_value<int>();

            if (con.first == "y")
                p.y = con.second.get_value<int>();

            if (con.first == "z")
                p.z = con.second.get_value<int>();

            if (con.first == "width")
                sz.width = con.second.get_value<int>();

            if (con.first == "height")
                sz.height = con.second.get_value<int>();

            if (con.first == "length")
                sz.length = con.second.get_value<int>();
        }

        int elem_enum = get_elem_enum(elem_type);

        obj_stat.emplace_back(elem_enum, p, sz);
    }
}




