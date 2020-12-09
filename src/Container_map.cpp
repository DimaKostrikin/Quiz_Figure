#include "Container_map.h"


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

Container_map::Container_map(std::shared_ptr<Scene> scene) {
    cur_id=0;
    for (auto &i: scene->container){
        float x = abs(i.vertices[0] - i.vertices[16]);
        float y = abs(i.vertices[1] - i.vertices[17]);
        float z = abs(i.vertices[3] - i.vertices[20]);
        switch(i.type){
            case START:
            case FINISH:
                //static_elems.push_back(Object_static obj());
                break;
        }
    }
}





