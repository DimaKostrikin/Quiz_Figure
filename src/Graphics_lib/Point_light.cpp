#include "Graphics_lib/Point_light.h"

Point_light::Point_light() {
    _position = glm::vec3(0.f, 0.f, 0.f);
    _ambient = glm::vec3(0.05f, 0.05f, 0.05f);
    _diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
    _specular = glm::vec3(1.0f, 1.0f, 1.0f);
    _constant = 1.f;
    _linear = 0.09f;
    _quadratic = 0.032f;
}

Point_light::Point_light(glm::vec3 position) {
    _position = position;
    _ambient = glm::vec3(0.05f, 0.05f, 0.05f);
    _diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
    _specular = glm::vec3(1.0f, 1.0f, 1.0f);
    _constant = 1.f;
    _linear = 0.09f;
    _quadratic = 0.032f;
}
Point_light::Point_light(glm::vec3 position, float constant, float linear, float quadratic) {
    _position = position;
    _ambient = glm::vec3(0.05f, 0.05f, 0.05f);
    _diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
    _specular = glm::vec3(1.0f, 1.0f, 1.0f);
    _constant = constant;
    _linear = linear;
    _quadratic = quadratic;
}

glm::vec3 Point_light::get_position() {
    return _position;
}
glm::vec3 Point_light::get_ambient() {
    return _ambient;
}
glm::vec3 Point_light::get_diffuse() {
    return _diffuse;
}
glm::vec3 Point_light::get_specular() {
    return _specular;
}
float Point_light::get_constant() {
    return _constant;
}
float Point_light::get_linear() {
    return _linear;
}
float Point_light::get_quadratic() {
    return _quadratic;
}

void Point_light::set_position(glm::vec3 position) {
    _position = position;
}
void Point_light::set_ambient(glm::vec3 ambient) {
    _ambient = ambient;
}
void Point_light::set_diffuse(glm::vec3 diffuse) {
    _diffuse = diffuse;
}
void Point_light::set_specular(glm::vec3 specular) {
    _specular = specular;
}
void Point_light::set_constant(float constant) {
    _constant = constant;
}
void Point_light::set_linear(float linear) {
    _linear = linear;
}
void Point_light::set_quadratic(float quadratic) {
    _quadratic = quadratic;
}