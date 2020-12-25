#include "Map_editor_lib/Map_parser.h"

std::string Map_parser::create_json(std::vector<Map_object> &map) {
    std::string file_name="filename.json";
    pt::ptree tree;

    const size_t MAP_SIZE = 1000;

    std::string text[22];
    text[0] = "SAVE";
    text[1] = "DELETE";
    text[2] = "PLAYER";
    text[3] = "WALL";
    text[4] = "WALL_STATIC";
    text[5] = "HINT";
    text[6] = "PLATFORM";
    text[7] = "STAIRS";
    text[8] = "START";
    text[9] = "FINISH";
    text[10] = "CUBE";
    text[11] = "BALL";
    text[12] = "DOOR";
    text[13] = "BUTTON";
    text[14] = "STEP";
    text[15] = "HOLE";
    text[16] = "FAN";
    text[17] = "TELEPORT";
    text[18] = "TELEPORT_IN";
    text[19] = "TELEPORT_OUT";
    text[20] = "LASER";
    text[21] = "JUMPER";

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
                size_t x = MAP_SIZE * i.x / width;
                size_t y = MAP_SIZE * i.y / height;
                size_t z = MAP_SIZE * i.z / height;
                size_t l = MAP_SIZE * i.l / height;
                size_t w = MAP_SIZE * i.w / width;
                size_t h = MAP_SIZE * i.h / height;
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
                size_t x = MAP_SIZE * i.x / width;
                size_t y = MAP_SIZE * i.y / height;
                size_t z = MAP_SIZE * i.z / height;
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
        if (!children[i].empty()) tree.add_child(text[i], children[i]);
    }

    // Сохранение дерева в JSON файл
    pt::write_json("filename.json", tree);
    pt::write_json(std::cout, tree);
    return file_name;
}
