//
// Created by moroz on 05.12.2020.
//

#ifndef QUIZ_FIGURE_INTERFACE_H
#define QUIZ_FIGURE_INTERFACE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <memory>
#include <functional>
#include <utility>
#include "Map_editor_handler.h"
#include "Menu.h"

#include "../stb_image.h"


// Константы
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


template<std::size_t N>
class Button_entry{
public:
    void draw(float (&vertices)[N], unsigned int &VAO, unsigned int &VBO, unsigned int &EBO){
        unsigned int indices[] = {
                0, 1, 3, // первый треугольник
                1, 2, 3  // второй треугольник
        };
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        int n = sizeof(float);
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


        // загрузка и создание текстуры
        // -------------------------
        unsigned int texture;
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
        unsigned char* data = stbi_load(file_cur.c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_set_flip_vertically_on_load(true);
        stbi_image_free(data);

        glBindTexture(GL_TEXTURE_2D, texture);


        // Рендеринг ящика
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
    void set_texture(std::string file_name){
        file_cur = std::move(file_name);
    }

    Button_entry(std::string f1, std::string f2):
                file_name_passive(std::move(f1)),
                file_name_active(std::move(f2)){
        deactivate();
    };

    void activate(){
        set_texture(file_name_active);
        activated = true;
    }

    void deactivate(){
        set_texture(file_name_passive);
        activated = false;
    }


    ~Button_entry(){
    }

    bool is_activated(){
        return activated;
    }

    //std::function<void()> action;
private:
    std::string file_cur;
    std::string file_name_active;
    std::string file_name_passive;

    bool activated;
};

class Interface {
public:
    Interface();
    ~Interface();
    void cycle();
    std::function<void()> draw;
    void start_draw();
    Button_entry<32> button_start;
    Button_entry<32> button_map_editor;


private:
    GLFWwindow *window;
    int shaderProgram;
    void processInput();
    float color;
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

#endif //QUIZ_FIGURE_INTERFACE_H

