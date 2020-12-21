#include "Map_parser.h"

//std::vector<Map_object> map
std::string Map_parser::create_json(std::vector<Map_object> map) {
    std::string file_name="../new.json";
    pt::ptree tree;
    std::ofstream out;
    out.open(file_name);
    if (!out.is_open()){
        std::cout << "error";
    }

    const size_t MAP_SIZE = 1000;


    for (auto &i: map){
        pt::ptree child1;
        switch (i.type){
            case WALL_STATIC:
            case WALL:
            case HOLE:
            case PLATFORM:
            case TELEPORT_IN:
            case TELEPORT_OUT:
            case CUBE:{
                size_t x = MAP_SIZE * i.x / i.SCR_WIDTH;
                size_t y = MAP_SIZE * i.y / i.SCR_HEIGHT;
                child1.put("id", i.id);
                child1.put("x", x);
                child1.put("y", y);
                child1.put("z", i.z);
                child1.put("l", i.l);
                child1.put("w", i.w);
                child1.put("h", i.h);
                child1.put("act_id", i.connect);
                tree.add_child(std::to_string(i.type), child1);
                //
            }
                break;

            case FINISH:
                child1.put("act_id", i.connect);
            case START:{
                size_t x = MAP_SIZE * i.x / i.SCR_WIDTH;
                size_t y = MAP_SIZE * i.y / i.SCR_HEIGHT;
                child1.put("id", i.id);
                child1.put("x", x);
                child1.put("y", y);
                child1.put("z", i.z);
                tree.add_child(std::to_string(i.type), child1);
                //
            }
                break;
            case JUMPER: {
                size_t power_height;
                for (auto &j: map) {
                    if (j.id == i.connect) {
                        power_height = j.h;
                        break;
                    }
                }
                size_t x = MAP_SIZE * i.x / i.SCR_WIDTH;
                size_t y = MAP_SIZE * i.y / i.SCR_HEIGHT;
                child1.put("id", i.id);
                child1.put("x", x);
                child1.put("y", y);
                child1.put("z", i.z);
                child1.put("l", i.l);
                child1.put("w", i.w);
                child1.put("h", i.h);
                child1.put("act_id", i.connect);
                tree.add_child(std::to_string(i.type), child1);
            }
        }
    }



    // Сохранение дерева в JSON файл
    pt::write_json(out, tree);
    pt::write_json("filename.json", tree);
    pt::write_json(std::cout, tree);
    out.close();

    // если так не стакается, то делаем вектор для каждого типа, пушим, проходимся
    return file_name;
}

void Map_parser::create_map() {
    //парсинг объектов

}