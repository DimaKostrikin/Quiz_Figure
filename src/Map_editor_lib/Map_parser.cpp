#include "Map_editor_lib/Map_parser.h"

std::string Map_parser::create_json(std::vector<Map_object> &map) const {
    std::string file_name="filename.json";
    pt::ptree tree;

    const float MAP_SIZE = SCR_HEIGHT / 50;


    std::string text[22];
    text[0] = "save";
    text[1] = "delete";
    text[2] = "players";
    text[3] = "walls";
    text[4] = "walls"; //walls_static
    text[5] = "hints";
    text[6] = "platforms";
    text[7] = "stairs";
    text[8] = "start";
    text[9] = "finish";
    text[10] = "cubes";
    text[11] = "balls";
    text[12] = "doors";
    text[13] = "buttons";
    text[14] = "steps";
    text[15] = "holes";
    text[16] = "fans";
    text[17] = "teleports";
    text[18] = "teleports_in";
    text[19] = "teleports_out";
    text[20] = "lasers";
    text[21] = "jumpers";

    pt::ptree child;

    std::valarray<pt::ptree> children (COUNT);
    child.put("x", 0);
    child.put("y",0);
    child.put("z", 0);
    child.put("length", 50);
    child.put("width", 50);
    child.put("height", 0.1);
    children[WALL].push_back(std::make_pair("", child));

    for (auto &i: map){
        pt::ptree child1, child2;
        switch (i.type){
            case WALL_STATIC:
                i.type = WALL;
            case WALL:
            case HOLE:
            case PLATFORM:
            case TELEPORT_IN:
            case TELEPORT_OUT:
            case CUBE:
            case JUMPER:{
                float x = MAP_SIZE * i.x / width;
                float y = MAP_SIZE * i.y / height;
                float z = MAP_SIZE * i.z / height;
                float l = MAP_SIZE * i.l / height;
                float w = MAP_SIZE * i.w / width;
                float h = MAP_SIZE * i.h / height;
                child1.put("id", i.id);
                child1.put("x", std::to_string(x));
                child1.put("y", std::to_string(y));
                child1.put("z", std::to_string((z+h)/2));
                child1.put("length", std::to_string(l));
                child1.put("width", std::to_string(w));
                child1.put("height", std::to_string(h));
                child1.put("act_id", i.connect);
                children[i.type].push_back(std::make_pair("", child1));
                //
            }
                break;

            case FINISH:
                child1.put("act_id", i.connect);
            case START:{
                float x = MAP_SIZE * i.x / width;
                float y = MAP_SIZE * i.y / height;
                float z = MAP_SIZE * i.z / height;
                child1.put("id", i.id);
                child1.put("x", std::to_string(x));
                child1.put("y", std::to_string(y));
                child1.put("z", std::to_string(z));
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
