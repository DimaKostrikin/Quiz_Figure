#include "Scene.h"

Scene::Scene() {
    //рисует все и создает сеточку
}

void Scene::init_label() {
    //создаем в shared_ptr Parameters_label
    //отрисовываем
    //держим, пока ссылка активна - иначе удалилось
}

void Scene::change_object(std::shared_ptr<Object> obj) {
    //меняет объект

}

void Scene::clear_object(std::shared_ptr<Object> obj) {
    //стирает объект
}
void Scene::draw_object(std::shared_ptr<Object> obj) {

    //рисует объект
}
