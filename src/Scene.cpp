#include "../include/Scene.h"

Scene::Scene() {
    //рисует все и создает сеточку
    grid_maker();
    label = nullptr;
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
