#include "Map_editor_handler.h"


Map_editor_handler::Map_editor_handler() {
    scene_init();
    toolbar_init();
    window= nullptr;
}

Map_editor_handler::Map_editor_handler(GLFWwindow *window) {
    this->window = window;
    scene_init();
    toolbar_init();
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
    glClearColor(0.51f, 0.73f, 0.73f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    float vertices[] = {
            // координаты

            0.7f,  0.9f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // верхняя правая
            0.7f, -0.9f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // нижняя правая
            -0.5, -0.9f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // нижняя левая
            -0.5f, 0.9f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f

    };

    unsigned int indices[] = {  // помните, что мы начинаем с 0!
            0, 1, 3,   // первый треугольник
            1, 2, 3    // второй треугольник
    };

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO); // мы также можем генерировать несколько VAO или буферов одновременно
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);



// Шаг №1: Копируем наш массив вершин в вершинный буфер
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

// Шаг №2: Копируем наш индексный массив в элементный буфер
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

// Шаг №3: Устанавливаем указатели вершинных атрибутов
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

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
    toolbar_init();


}