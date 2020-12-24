#ifndef PROJECT_QUIZ_FIGURE_POINT_LIGHT_H
#define PROJECT_QUIZ_FIGURE_POINT_LIGHT_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Point_light {
private:
    glm::vec3 _position;
    glm::vec3 _ambient;
    glm::vec3 _diffuse;
    glm::vec3 _specular;
    float _constant;
    float _linear;
    float _quadratic;
public:
    Point_light();
    Point_light(glm::vec3 position);
    Point_light(glm::vec3 position, float constant, float linear, float quadratic);
    glm::vec3 get_position();
    glm::vec3 get_ambient();
    glm::vec3 get_diffuse();
    glm::vec3 get_specular();
    float get_constant();
    float get_linear();
    float get_quadratic();

    void set_position(glm::vec3 position);
    void set_ambient(glm::vec3 ambient);
    void set_diffuse(glm::vec3 diffuse);
    void set_specular(glm::vec3 specular);
    void set_constant(float constant);
    void set_linear(float linear);
    void set_quadratic(float quadratic);
};

#endif //PROJECT_QUIZ_FIGURE_POINT_LIGHT_H
