#include "Map_parser.h"

std::string Map_parser::create_json(std::shared_ptr<Container_map> map) {
    std::string file_name;
    if (parser(map, file_name)) {};


    return file_name;
}

bool Map_parser::parser(std::shared_ptr<Container_map> map, std::string file_name) {
    //парсинг объектов

}