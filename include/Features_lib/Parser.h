#ifndef PARSER_H
#define PARSER_H
#include "Objects.h"
#include <list>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <iostream>
#include <string>

class Parser {
private:
    std::list<Object_dynamic>& obj_dyn;
    std::list<Object_static>& obj_stat;
    std::list<Object_activated>& obj_acted;
    std::list<Object_activator>& obj_actor;
    std::list<Object_influence>& obj_infl;
    boost::property_tree::ptree pt_json;

private:
    int get_elem_enum(const std::string &elem_type);
    void clear_lists();
    void fill_static(const std::string &elem_type);
    void fill_dynamic(const std::string &elem_type);
    void fill_acted(const std::string &elem_type);
    void fill_actor(const std::string &elem_type);

    std::vector<std::string> names_static;
    std::vector<std::string> names_dynamic;
    std::vector<std::string> names_acted;
    std::vector<std::string> names_actor;
public:
    Parser(std::list<Object_dynamic>& obj_dyn,
           std::list<Object_static>& obj_stat,
           std::list<Object_activated>& obj_acted,
           std::list<Object_activator>& obj_actor,
           std::list<Object_influence>& obj_infl);
    void fill_from(std::string path_to_json);
};


#endif // PARSER_H
