//
// Created by moroz on 07.12.2020.
//

#ifndef QUIZ_FIGURE_BUTTON_ENTRY_H
#define QUIZ_FIGURE_BUTTON_ENTRY_H


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../Objects.h"

#include <iostream>
#include <memory>
#include <functional>
#include <utility>

#include "../stb_image.h"

template<std::size_t N>
class Button_entry{
public:

    //Button_entry( Button_entry<N>&& o) = default;
    //Button_entry(const Button_entry<N>& o) = default;

    /*Button_entry(const Button_entry<N> &button_entry) :
            file_name_passive(button_entry.file_name_passive),
            file_name_active(button_entry.file_name_active),
            vertices(std::move(button_entry.vertices)){}*/


    std::vector<float> vertices;

    void texture_gen(unsigned int &texture, const std::string& filename){
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
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);
    }

    void draw(unsigned int &VAO, unsigned int &VBO, unsigned int &EBO);
    void set_texture(unsigned int texture);

    Button_entry(std::string f1, std::string f2, std::vector<float> vertices):
            file_name_passive(std::move(f1)),
            file_name_active(std::move(f2)), activated(false), vertices(std::move(vertices)){
        // загрузка и создание текстуры
        // -------------------------
        texture_gen(texture_active, file_name_active);
        texture_gen(texture_passive, file_name_passive);
        texture_cur = texture_passive;

    }

    void activate();

    void deactivate();

    ~Button_entry()= default;

    bool is_activated(){
        return activated;
    }

    //std::function<void()> action;
private:
    std::string file_name_active;
    std::string file_name_passive;
    unsigned int texture_cur, texture_active, texture_passive;
    bool activated;
};

template<std::size_t N>
void Button_entry<N>::activate(){
    set_texture(texture_active);
    activated = true;
}

template<std::size_t N>
void Button_entry<N>::deactivate(){
    set_texture(texture_passive);
    activated = false;
}

template<std::size_t N>
void Button_entry<N>::draw(unsigned int &VAO, unsigned int &VBO, unsigned int &EBO){
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
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
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

}

template<std::size_t N>
void Button_entry<N>::set_texture(unsigned int texture){
    texture_cur = texture;
}

template<std::size_t N>
class Button_toolbar : public Button_entry<N>{


public:
    Button_toolbar(std::string f1, std::string f2, std::vector<float> vertices, type_elem type): Button_entry<N>(f1, f2, vertices), type(type){

    }
    type_elem type;
};

template<std::size_t N>
class Map_object: public Button_entry<N>{
public:
    type_elem type;
   // Map_object(Map_object<N>&& o) = default;
    //Map_object(const Map_object<N>& o) = default;
    Map_object(std::string f1, std::string f2, std::vector<float> vertices, type_elem type):
            Button_entry<N>(f1, f2, vertices), type(type){}
    void up(){
        if (this->vertices[1] < 1.0f) {
            this->vertices[1] += 0.01f;
            this->vertices[9] += 0.01f;
            this->vertices[17] += 0.01f;
            this->vertices[25] += 0.01f;
        }
    }
    void down(){
        if (this->vertices[17] > -1.0f) {
            this->vertices[1] -= 0.01f;
            this->vertices[9] -= 0.01f;
            this->vertices[17] -= 0.01f;
            this->vertices[25] -= 0.01f;
        }
    }

    void right(){
        if (this->vertices[0] < 1.0f) {
            this->vertices[0] += 0.01f;
            this->vertices[8] += 0.01f;
            this->vertices[16] += 0.01f;
            this->vertices[24] += 0.01f;
        }
    }
    void left(){
        if (this->vertices[16] > -1.0f) {
            this->vertices[0] -= 0.01f;
            this->vertices[8] -= 0.01f;
            this->vertices[16] -= 0.01f;
            this->vertices[24] -= 0.01f;
        }
    }

    ~Map_object(){}
    /*Map_object(const Map_object<N> &elem) : Button_entry<N>(elem){}*/

};

#endif //QUIZ_FIGURE_BUTTON_ENTRY_H
