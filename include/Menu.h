//
// Created by moroz on 06.12.2020.
//

#ifndef QUIZ_FIGURE_MENU_H
#define QUIZ_FIGURE_MENU_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <memory>
#include <functional>
#include <utility>
#include "Map_editor_handler.h"

#include "../stb_image.h"

template<std::size_t N>
class Button_entry{
public:
    unsigned int texture_cur, texture_active, texture_passive;

    void texture_gen(unsigned int &texture, std::string filename){
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
        stbi_set_flip_vertically_on_load(true);
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

    bool activated;
};

class Menu {
public:
    Menu(GLFWwindow *window);
    ~Menu(){};
    void draw_menu();
    Button_entry<32> button_start;
    Button_entry<32> button_map_editor;
    std::shared_ptr<Map_editor_handler> map_editor_handler;
    std::function<void()> draw;
    std::function<void()> processInput;
    void process_input();

private:
    GLFWwindow *window;

};



#endif //QUIZ_FIGURE_MENU_H
