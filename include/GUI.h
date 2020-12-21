//
// Created by moroz on 07.12.2020.
//

#ifndef QUIZ_FIGURE_GUI_H
#define QUIZ_FIGURE_GUI_H


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
    const size_t N = 32;
    std::vector<float> vertices;
    static void texture_gen(unsigned int &texture, const std::string& filename);

    void draw(unsigned int &VAO, unsigned int &VBO, unsigned int &EBO);

    Elem(std::string f1, std::vector<float> vertices):
            vertices(std::move(vertices)){
        // загрузка и создание текстуры
        texture_gen(texture_passive, std::move(f1));
        texture_cur = texture_passive;
    }

    ~Elem()= default;


protected:
    unsigned int texture_cur, texture_passive;
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
    int x, y, z;
    int h, w, l;
   // Map_object(Map_object<N>&& o) = default;
    //Map_object(const Map_object<N>& o) = default;
    Map_object(std::string f1, std::string f2, std::vector<float> vertices, type_elem type, size_t id,
               const unsigned int &SCR_HEIGHT, const unsigned int &SCR_WIDTH):
            Button_entry(std::move(f1), std::move(f2), std::move(vertices)),
            id(id), SCR_HEIGHT(SCR_HEIGHT), SCR_WIDTH(SCR_WIDTH), connect(0),type(type), z(0){change_w(); change_l();};

    void up();
    void down();
    void right();
    void left();
    void up_z();
    void down_z();
    void plus_width();
    void minus_width();
    void plus_height();
    void minus_height();
    void minus_length();
    void plus_length();
    bool check_elem();
    void change_w();
    void change_l();
    void change_x();
    void change_y();
    void change_z();


    bool check_border_right();
    bool check_border_left();
    bool check_border_up();
    bool check_border_down();
    bool check_border();
    Map_object& operator= (const Map_object &elem);

    bool is_activator();
    bool is_activated();
    bool is_dynamic();

    ~Map_object()=default;
    /*Map_object(const Map_object<N> &elem) : Button_entry<N>(elem){}*/
private:

    const unsigned int SCR_HEIGHT;
    const unsigned int SCR_WIDTH;
};

#endif //QUIZ_FIGURE_GUI_H
