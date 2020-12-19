//
// Created by moroz on 07.12.2020.
//

#include "Map_editor_lib/GUI.h"

//генерация текстуры
void Elem::texture_gen(unsigned int &texture, const std::string& filename){
    stbi_set_flip_vertically_on_load(true);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture); // все последующие GL_TEXTURE_2D-операции теперь будут влиять на данный текстурный объект
    // установка параметров наложения текстуры
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// установка метода наложения текстуры GL_REPEAT (стандартный метод наложения)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // установка параметров фильтрации текстуры
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // загрузка изображения, создание текстуры и генерирование mipmap-уровней
    int width, height, nrChannels;
    unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrChannels, 0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    if (data)
    {

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}

void Elem::draw(unsigned int &VAO, unsigned int &VBO, unsigned int &EBO){
    unsigned int indices[] = {
            0, 1, 3, // первый треугольник
            1, 2, 3  // второй треугольник
    };
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    float new_vertices[N];

    for ( size_t i = 0; i < N; ++i )
        new_vertices[i] = vertices[i];
    glBufferData(GL_ARRAY_BUFFER, sizeof(new_vertices), new_vertices, GL_STATIC_DRAW);


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // координатные атрибуты
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)nullptr);
    glEnableVertexAttribArray(0);
    // цветовые атрибуты
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // атрибуты текстурных координат
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindTexture(GL_TEXTURE_2D, texture_cur);


    // Рендеринг ящика
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

}

void Button_entry::set_texture(unsigned int texture){
    texture_cur = texture;
}

void Button_entry::activate(){
    set_texture(texture_active);
    activated = true;
}


void Button_entry::deactivate(){
    set_texture(texture_passive);
    activated = false;
}



void Map_object::up(){
    if (this->vertices[1] < 0.9f) {
        this->vertices[1] += 0.01f;
        this->vertices[9] += 0.01f;
        this->vertices[17] += 0.01f;
        this->vertices[25] += 0.01f;
    }
}
void Map_object::down(){
    if (this->vertices[17] > -0.9f) {
        this->vertices[1] -= 0.01f;
        this->vertices[9] -= 0.01f;
        this->vertices[17] -= 0.01f;
        this->vertices[25] -= 0.01f;
    }
}

void Map_object::right(){
    if (this->vertices[0] < 0.7f) {
        this->vertices[0] += 0.01f;
        this->vertices[8] += 0.01f;
        this->vertices[16] += 0.01f;
        this->vertices[24] += 0.01f;
    }
}
void Map_object::left(){
    if (this->vertices[16] > -0.5f) {
        this->vertices[0] -= 0.01f;
        this->vertices[8] -= 0.01f;
        this->vertices[16] -= 0.01f;
        this->vertices[24] -= 0.01f;
    }
}

Map_object &Map_object::operator=(const Map_object &elem) {
    texture_passive = elem.texture_passive;
    texture_active = elem.texture_active;
    texture_cur = elem.texture_cur;
    activated = elem.activated;
    return *this;
}

bool Map_object::is_activator() {
    return ((type == HOLE) || (type == STEP));
}

bool Map_object::is_activated() {
    return ((type == DOOR) || (type == BUTTON) || (type == FINISH) );
}

bool Map_object::is_dynamic() {
    return ((type == CUBE) || (type == BALL));
}