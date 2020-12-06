#include "Map_editor_handler.h"


Map_editor_handler::Map_editor_handler() {
    scene_init();
    toolbar_init();
}

Map_editor_handler::Map_editor_handler(GLFWwindow *window) {
    this->window = window;
    scene_init();
    toolbar_init();
    color = 1.0f;
}

void Map_editor_handler::on_mouse_click() {
    //нажатие на объект
/*
    //если объект существующий
    //тут еще айди объекта передает
    scene->init_label();

    //нажатие на тулбар элемент
    //по кейсу создаем элемент
    std::shared_ptr<Object> obj;
    map->add_object(obj);
    scene->draw_object(obj);

    //нажатие на label
    //принимает новое состояние
    scene->label->changed();

    //нажатие save
    parser.create_json(map);*/



}

void Map_editor_handler::scene_init() {
    //создание сцены
}

void Map_editor_handler::toolbar_init() {
    //создание тулбара с инструментами
}

void Map_editor_handler::on_key_click() {
    /*//перемещение элемента по полю по сетке
    std::shared_ptr<Object> obj;
    //доп параметром добавить кнопку
    //стирает объект
    scene->clear_object(obj);
    map->change_object( obj);
    //перерисовывает элемент
    scene->change_object(obj);*/
}

Map_editor_handler::~Map_editor_handler() {

}

void Map_editor_handler::draw() {
    glClearColor(1.0f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    unsigned int VBO, VAO, EBO;
    glGenBuffers(1, &EBO);

    glGenVertexArrays(1, &VAO); // мы также можем генерировать несколько VAO или буферов одновременно
    glGenBuffers(1, &VBO);


    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}