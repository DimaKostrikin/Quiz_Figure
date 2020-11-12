#include "Container_map.h"

Container_map::Container_map() {
    cur_elem_id = 0;
}

void Container_map::add_object(std::shared_ptr<Object>) {
    //смотрит тип и добавляет в соответствующий контейнер
}

std::shared_ptr<Object> Container_map::get_object(size_t id) {
    //смотрит по контейнерам и возвращает ссылку на объект
}

void Container_map::change_object(std::shared_ptr<Object>) {
    //мб позволить внешним сущностям это смену осуществлять, тогда change не нужен
}

void Container_map::delete_object(std::shared_ptr<Object>) {
    //удаляем объект из контейнера
}

size_t Container_map::get_unique_id() {
    //в объекте поле мб айдишник и не понадобится
    ++cur_elem_id;
    return cur_elem_id;
}

Container_map::~Container_map() {

}





