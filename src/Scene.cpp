#include "../include/Scene.h"

std::vector<float> vertices_paper = {
        // координаты

        0.7f,  0.7f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f,   // верхняя правая
        0.7f, -0.7f, 0.0f,  1.0f, 1.0f, 1.0f,   1.0f, 0.0f,   // нижняя правая
        -0.7f, -0.7f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f,   // нижняя левая
        -0.7f, 0.7f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f

};


Scene::Scene(): paper("textures/white.png", vertices_paper), id(0) {

    cur_elem = 0;
    connection_mode = false;
    //рисует все и создает сеточку
    //label = nullptr;
}

void Scene::init_label() {
    //создаем в shared_ptr Parameters_label
    //отрисовываем
    //держим, пока ссылка активна - иначе удалилось
}

void Scene::change_object(std::shared_ptr<Object> obj) {
    //меняет объект
    //возможно обойтись только cl_obj и draw_obj?

}

void Scene::clear_object(std::shared_ptr<Object> obj) {
    //стирает объект
}
void Scene::draw_object(std::shared_ptr<Object> obj) {

    //рисует объект
}

void Scene::grid_maker() {
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO); // мы также можем генерировать несколько VAO или буферов одновременно
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    paper.draw(VAO, VBO, EBO);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Scene::draw() {
    grid_maker();
    for(auto &i: container)
    {
        unsigned int VBO, VAO, EBO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
        i.draw(VAO, VBO, EBO);

        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
    }
}

void Scene::delete_elem() {
    if (!container.empty()) {
        if (container[cur_elem].is_active()) {
            size_t c = container[cur_elem].connect;
            container[cur_elem] = container[container.size()-1];
            container[cur_elem].id = container[container.size()-1].id;
            container[cur_elem].vertices = container[container.size()-1].vertices;
            container[cur_elem].type = container[container.size()-1].type;
            container.pop_back();
            for (auto &i: container){
                if (i.connect == c) i.connect = 0;
            }
            //std::swap(container[cur_elem], container[container.size() - 1]);
            //container.pop_back();
        }
    }
}
