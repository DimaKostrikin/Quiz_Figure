//
// Created by moroz on 07.12.2020.
//

#ifndef QUIZ_FIGURE_ELEMENTS_H
#define QUIZ_FIGURE_ELEMENTS_H


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../Objects.h"

#include <iostream>
#include <memory>
#include <functional>
#include <utility>

#include "../stb_image.h"

class Elem{
public:

    std::vector<float> vertices;

    void draw(unsigned int &VAO, unsigned int &VBO, unsigned int &EBO);

    Elem(std::string f1, std::vector<float> vertices):
            vertices(std::move(vertices)){
        // загрузка и создание текстуры
        texture_gen(texture_passive, std::move(f1));
        texture_cur = texture_passive;
    }

    ~Elem()= default;


protected:
    const size_t N = 32;
    unsigned int texture_cur, texture_passive;
    static void texture_gen(unsigned int &texture, const std::string& filename);
private:

};


class Button_entry : public Elem{
public:

    void set_texture(unsigned int texture);

    Button_entry(std::string f1, std::string f2, std::vector<float> vertices):
            Elem(std::move(f1), std::move(vertices)),
            activated(false){
        // загрузка и создание текстуры
        texture_gen(texture_active, f2);
    }


    void activate();

    void deactivate();

    ~Button_entry()= default;

    bool is_active() const {
        return activated;
    }


protected:
    unsigned int texture_active;
    bool activated;
};



class Button_toolbar : public Button_entry{
public:
    Button_toolbar(std::string f1, std::string f2,
                   std::vector<float> vertices, type_elem type):
                   Button_entry(std::move(f1), std::move(f2), std::move(vertices)), type(type){};
    type_elem type;
    ~Button_toolbar()=default;
private:

};

class Map_object: public Button_entry{
public:
    size_t id;
    size_t connect;
    type_elem type;

    Map_object(std::string f1, std::string f2, std::vector<float> vertices, type_elem type, size_t id,
               const unsigned int &SCR_HEIGHT, const unsigned int &SCR_WIDTH);

    void up();
    void down();
    void right();
    void left();
    void up_z();
    void down_z();
    void plus_width(float &rborder, float &lborder, float &tborder, float &bborder);
    void minus_width();
    void plus_height();
    void minus_height();
    void minus_length();
    void plus_length(float &rborder, float &lborder, float &tborder, float &bborder);
    bool check_elem();
    void change_w();
    void change_l();
    void change_x();
    void change_y();


    bool check_border_right(float &border);
    bool check_border_left(float &border);
    bool check_border_up(float &border);
    bool check_border_down(float &border);
    bool check_border(float &rborder, float &lborder, float &tborder, float &bborder);
    Map_object& operator= (const Map_object &elem);

    bool is_activator();
    bool is_activated();
    bool is_dynamic();
    bool is_static();
    // for jumper - connected object
    bool is_connected();

    ~Map_object()=default;

    const unsigned int SCR_HEIGHT;
    const unsigned int SCR_WIDTH;

    int x, y, z;
    int h, w, l;

private:

};

#endif //QUIZ_FIGURE_ELEMENTS_H
