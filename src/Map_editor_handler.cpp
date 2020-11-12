#include "Map_editor_handler.h"

Map_editor_handler::Map_editor_handler() {
    scene_init();
    toolbar_init();
}

void Map_editor_handler::on_mouse_click() {
    bool condition = true;
    //нажатие на объект
    if (condition){
        //если объект существующий
        //тут еще айди объекта передает
        scene->init_label();
    }
    //нажатие на тулбар элемент
    //по кейсу создаем элемент
    std::shared_ptr<Object> obj;
    map->add_object(obj);
    scene->draw_object(obj);

    //нажатие на label



}

void Map_editor_handler::scene_init() {
    //создание сцены
}

void Map_editor_handler::toolbar_init() {
    //создание тулбара с инструментами
}

void Map_editor_handler::on_key_click() {
    //перемещение элемента по полю по сетке
    std::shared_ptr<Object> obj;
    //доп параметром добавить кнопку
    //стирает объект
    scene->clear_object(obj);
    map->change_object( obj);
    //перерисовывает элемент
    scene->change_object(obj);
}