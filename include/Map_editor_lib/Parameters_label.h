//
// Created by moroz on 12.11.2020.
//

#ifndef QUIZ_FIGURE_PARAMETERS_LABEL_H
#define QUIZ_FIGURE_PARAMETERS_LABEL_H

#include <iostream>
#include <map>
#include "memory"
#include "Features_lib/Objects.h"

#include <ft2build.h>
#include FT_FREETYPE_H
#include "Map_editor_lib/shader_s.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Elements.h"


struct Character {
    unsigned int TextureID; // ID текстуры глифа
    glm::ivec2 Size; // размер глифа
    glm::ivec2 Bearing; // смещение от линии шрифта до верхнего/левого угла глифа
    unsigned int Advance; // смещение до следующего глифа
};


class Parameters_label{
public:
    Parameters_label();
    ~Parameters_label() = default;

    void set_object(std::shared_ptr<Map_object> object);
    std::shared_ptr<Map_object> get_object();
    void draw();
    void RenderText(unsigned int &VAO, unsigned int &VBO,Shader& shader, std::string text, float x, float y, float scale, glm::vec3 color);
private:
    std::map<GLchar, Character> characters;
    std::string label;
    std::shared_ptr<Map_object> obj;
    Shader shader;

};

#endif //QUIZ_FIGURE_PARAMETERS_LABEL_H
