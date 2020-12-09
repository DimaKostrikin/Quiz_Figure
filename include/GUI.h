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

    bool is_activated() const{
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
    type_elem type;
   // Map_object(Map_object<N>&& o) = default;
    //Map_object(const Map_object<N>& o) = default;
    Map_object(std::string f1, std::string f2, std::vector<float> vertices, type_elem type):
            Button_entry(std::move(f1), std::move(f2), std::move(vertices)), type(type){};

    void up();
    void down();
    void right();
    void left();

    Map_object& operator= (const Map_object &elem);

    ~Map_object()=default;
    /*Map_object(const Map_object<N> &elem) : Button_entry<N>(elem){}*/
private:

};

#endif //QUIZ_FIGURE_GUI_H
