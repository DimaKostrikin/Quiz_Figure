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
               obj_infl(obj_infl) {
    names_static.emplace_back("walls");
    names_static.emplace_back("lights");
    names_static.emplace_back("platforms");
    //names_static.emplace_back("stairs");

    names_dynamic.emplace_back("cubes");
    names_dynamic.emplace_back("balls");

    names_acted.emplace_back("doors");

    names_actor.emplace_back("fans");
    names_actor.emplace_back("teleports-in");
    names_actor.emplace_back("teleports-out");
    names_actor.emplace_back("holes");
}

void Parser::fill_from(std::string path_to_json) {
    boost::property_tree::read_json(path_to_json, pt_json);
    boost::property_tree::ptree::const_iterator end = pt_json.end();

    clear_lists();

    for (auto it = names_static.begin(); it != names_static.end(); ++it) {
        fill_static(*it);
    }

    for (auto it = names_dynamic.begin(); it != names_dynamic.end(); ++it) {
        fill_dynamic(*it);
    }

    for (auto it = names_acted.begin(); it != names_acted.end(); ++it) {
        fill_acted(*it);
    }

    for (auto it = names_actor.begin(); it != names_actor.end(); ++it) {
        fill_actor(*it);
    }


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
    Point p = {0, 0, 0};
    Size sz = {0, 0, 0};
    unsigned int id = 0;

    auto child = pt_json.get_child_optional(elem_type);
    if (child) {
        for (auto &wall : pt_json.get_child(elem_type)) {
            for (auto &con : wall.second.get_child("")) {
                std::cout << con.first << ": " << con.second.data() << std::endl;
                if (con.first == "id")
                    id = con.second.get_value<int>();

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

            Object_static emplaced(elem_enum, p, sz);
            emplaced.get_id() = id;
            obj_stat.push_back(emplaced);
        }
    }
}

void Parser::fill_dynamic(const std::string &elem_type) {
    Point p = {0, 0, 0};
    Size sz = {0, 0, 0};
    glm::vec3 speed = {0, 0, 0};
    unsigned int id = 0;

    auto child = pt_json.get_child_optional(elem_type);
    if (child) {
        for (auto &wall : pt_json.get_child(elem_type)) {
            for (auto &con : wall.second.get_child("")) {
                std::cout << con.first << ": " << con.second.data() << std::endl;
                if (con.first == "id")
                    id = con.second.get_value<int>();

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

                if (con.first == "dx")
                    speed.x = con.second.get_value<int>();

                if (con.first == "dy")
                    speed.y = con.second.get_value<int>();

                if (con.first == "dz")
                    speed.z = con.second.get_value<int>();
            }
            int elem_enum = get_elem_enum(elem_type);

            Object_dynamic emplaced(elem_enum, p, sz, speed);
            emplaced.get_id() = id;

            obj_dyn.push_back(emplaced);
        }
    }

}

void Parser::fill_acted(const std::string &elem_type) {
    Point p = {0, 0, 0};
    Size sz = {0, 0, 0};
    unsigned int id = 0;

    auto child = pt_json.get_child_optional(elem_type);
    if (child) {
        for (auto &wall : pt_json.get_child(elem_type)) {
            for (auto &con : wall.second.get_child("")) {
                std::cout << con.first << ": " << con.second.data() << std::endl;
                if (con.first == "id")
                    id = con.second.get_value<int>();

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
            Object_activated emplaced(elem_enum, p, sz);

            emplaced.get_id() = id;

            obj_acted.push_back(emplaced);
        }
    }
}

void Parser::fill_actor(const std::string &elem_type) {
    Point p = {0, 0, 0};
    Size sz = {0, 0, 0};

    unsigned int id = 0;
    unsigned int act_id = 999999;  // чтобы не попалось значение

    auto child = pt_json.get_child_optional(elem_type);
    if (child) {
        for (auto &wall : pt_json.get_child(elem_type)) {
            for (auto &con : wall.second.get_child("")) {
                std::cout << con.first << ": " << con.second.data() << std::endl;
                if (con.first == "id")
                    id = con.second.get_value<int>();

                if (con.first == "act_id")
                    act_id = con.second.get_value<int>();

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

            for (auto it = obj_acted.begin(); it != obj_acted.end(); ++it) {
                if (it->get_id() == act_id) {
                    Object_activator emplaced(elem_enum, p, sz, it);
                    emplaced.get_id() = id;
                    obj_actor.push_back(emplaced);
                }
            }
        }
    }
}












