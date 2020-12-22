#include "Map_parser.h"

//std::vector<Map_object> map
std::string Map_parser::create_json(std::vector<Map_object> map) {
    std::string file_name="filename.json";
    pt::ptree tree;

    const size_t MAP_SIZE = 1000;

    std::valarray<pt::ptree> children (COUNT);
    for (auto &i: map){
        pt::ptree child1, child2;
        switch (i.type){
            case WALL_STATIC:
            case WALL:
            case HOLE:
            case PLATFORM:
            case TELEPORT_IN:
            case TELEPORT_OUT:
            case CUBE:
            case JUMPER:{
                size_t x = MAP_SIZE * i.x / i.SCR_WIDTH;
                size_t y = MAP_SIZE * i.y / i.SCR_HEIGHT;
                size_t z = MAP_SIZE * i.z / i.SCR_HEIGHT;
                size_t l = MAP_SIZE * i.l / i.SCR_HEIGHT;
                size_t w = MAP_SIZE * i.w / i.SCR_WIDTH;
                size_t h = MAP_SIZE * i.h / i.SCR_HEIGHT;
                child1.put("id", i.id);
                child1.put("x", x);
                child1.put("y", y);
                child1.put("z", z);
                child1.put("l", l);
                child1.put("w", w);
                child1.put("h", h);
                child1.put("act_id", i.connect);
                children[i.type].push_back(std::make_pair("", child1));
                //
            }
                break;

            case FINISH:
                child1.put("act_id", i.connect);
            case START:{
                size_t x = MAP_SIZE * i.x / i.SCR_WIDTH;
                size_t y = MAP_SIZE * i.y / i.SCR_HEIGHT;
                size_t z = MAP_SIZE * i.z / i.SCR_HEIGHT;
                child1.put("id", i.id);
                child1.put("x", x);
                child1.put("y", y);
                child1.put("z", z);
                children[i.type].push_back(std::make_pair("", child1));
                //
            }
                break;
        }
    }

    for (int i = 0; i < children.size(); ++i){
        if (!children[i].empty()) tree.add_child(std::to_string(i), children[i]);
    }

    // Сохранение дерева в JSON файл
    pt::write_json("filename.json", tree);
    pt::write_json(std::cout, tree);
    return file_name;
}

void Map_parser::create_map() {

}