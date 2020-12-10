#include "Map_parser.h"

const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 1024;

//std::vector<Map_object> map
std::string Map_parser::create_json(std::vector<Map_object> map) {
    std::string file_name="../new.json";
    pt::ptree tree;
    std::ofstream out;
    out.open(file_name);
    if (!out.is_open()){
        std::cout << "error";
    }






    /*std::vector<float> vertices_button{
            // координаты

            0.2f, 0.2f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,   // верхняя правая
            0.2f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,   // нижняя правая
            0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,   // нижняя левая
            0.0f, 0.2f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f

    };


    Map_object a ("textures/start.jpg", "textures/start_act.jpg", vertices_button,
                                           START, 1);
    Map_object b ("textures/start.jpg", "textures/start_act.jpg", vertices_button,
                  FINISH, 2);

    Map_object c ("textures/start.jpg", "textures/start_act.jpg", vertices_button,
                  CUBE, 3);


    std::vector<Map_object> map;
    map.push_back(a);
    map.push_back(b);
    map.push_back(c);*/
    for (auto &i: map){
        double x1 = (i.vertices[16] + 1.0f) * (SCR_WIDTH / 2);
        double x2 = (i.vertices[0] + 1.0f) * (SCR_WIDTH / 2);
        double y1 = (1.0f - i.vertices[1]) * (SCR_HEIGHT / 2);
        double y2 = (1.0f - i.vertices[9]) * (SCR_HEIGHT / 2);
        pt::ptree child1;
        switch (i.type){
            case HOLE:
            case CUBE:{
                double x = x1+(x2 - x1)/2;
                double y = y1+(y2 - y1)/2;
                child1.put("id", i.id);
                child1.put("x", x);
                child1.put("y", y);
                child1.put("z", (150-0)/2);
                child1.put("a", 150); //длина стороны
                //if (i.connect!=0)
                child1.put("act_id", i.connect);
                tree.add_child(std::to_string(i.type), child1);
                //
            }
                break;

            case FINISH:
                child1.put("act_id", i.connect);
            case START:{
                double x = x1+(x2 - x1)/2;
                double y = y1+(y2 - y1)/2;
                child1.put("x", x);
                child1.put("y", y);
                child1.put("z", 0);
                tree.add_child(std::to_string(i.type), child1);
                //
            }

                break;
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