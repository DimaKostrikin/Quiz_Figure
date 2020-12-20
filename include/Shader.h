#ifndef PROJECT_QUIZ_FIGURE_SHADER_H
#define PROJECT_QUIZ_FIGURE_SHADER_H

#include <glad/glad.h> // подключаем glad для активации всех заголовочных файлов OpenGL

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
    //ID - идентификатор программы
    unsigned int ID;

    // Конструктор считывает данные и выполняет построение шейдера
    Shader(const char* vertexPath, const char* fragmentPath);

    //Использование/активация шейдера
    void use();

    //uniform-функции
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setVec2(const std::string& name, const glm::vec2& value) const;
    void setVec2(const std::string& name, float x, float y) const;
    void setVec3(const std::string& name, const glm::vec3& value) const;
    void setVec3(const std::string& name, float x, float y, float z) const;
    void setVec4(const std::string& name, const glm::vec4& value) const;
    void setVec4(const std::string& name, float x, float y, float z, float w) const;
    void setMat2(const std::string& name, const glm::mat2& mat) const;
    void setMat3(const std::string& name, const glm::mat3& mat) const;
    void setMat4(const std::string& name, const glm::mat4& mat) const;
private:
    //Функция для проверки ошибок компиляции/связывания шейдеров
    void checkCompileErrors(unsigned int shader, std::string type);
};



#endif //PROJECT_QUIZ_FIGURE_SHADER_H
