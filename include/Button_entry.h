//
// Created by moroz on 07.12.2020.
//

#ifndef QUIZ_FIGURE_BUTTON_ENTRY_H
#define QUIZ_FIGURE_BUTTON_ENTRY_H


#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <memory>
#include <functional>

#include "../stb_image.h"

template<std::size_t N>
class Button_entry{
public:

    void texture_gen(unsigned int &texture, std::string filename){
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

    void draw(float (&vertices)[N], unsigned int &VAO, unsigned int &VBO, unsigned int &EBO);
    void set_texture(unsigned int texture);

    Button_entry(std::string f1, std::string f2):
            file_name_passive(std::move(f1)),
            file_name_active(std::move(f2)), activated(false){
        // загрузка и создание текстуры
        // -------------------------
        texture_gen(texture_active, file_name_active);
        texture_gen(texture_passive, file_name_passive);
        texture_cur = texture_passive;

    }

    void activate();

    void deactivate();

    ~Button_entry(){}

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
void Button_entry<N>::draw(float (&vertices)[N], unsigned int &VAO, unsigned int &VBO, unsigned int &EBO){
    unsigned int indices[] = {
            0, 1, 3, // первый треугольник
            1, 2, 3  // второй треугольник
    };
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

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

#endif //QUIZ_FIGURE_BUTTON_ENTRY_H
