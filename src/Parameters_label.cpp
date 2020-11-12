#include "Parameters_label.h"

Parameters_label::Parameters_label(int obj_id) {
    //по obj_id ищем тайп и его передает
    switch (obj_id) {
        case 1:
            //параметры в зависимости от типа
            break;

        case 2:
            //параметры в зависимости от типа
            break;
        default:
            break;


    }
}

void Parameters_label::changed() {
    //изменения с объектом, свойства меняются в зависимости от того, что из parameters было изменено
}

void Parameters_label::close() {
    //деструктором заменить?
    //убирает объект, дает scene сигнал
}

Parameters_label::~Parameters_label() {

}

void Parameters_label::init() {
    //или в конструкторе все выполнить, или все case сюда запихнуть
}
