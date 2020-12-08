#include "../include/Scene.h"

Scene::Scene() {
    cur_elem = 0;
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
    //отрисовка сетки
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
