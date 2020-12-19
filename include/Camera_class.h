#ifndef PROJECT_QUIZ_FIGURE_CAMERA_CLASS_H
#define PROJECT_QUIZ_FIGURE_CAMERA_CLASS_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

// Определяет несколько возможных вариантов движения камеры
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Параметры камеры по умолчанию
const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float SPEED       =  2.5f;
const float SENSITIVITY =  0.1f;
const float ZOOM        =  45.0f;


// Класс камеры, который обрабатывает входные данные и вычисляет соответствующие Эйлеровы углы, векторы и матрицы для использования в OpenGL
class Camera
{
public:
    // Атрибуты камеры
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    // углы Эйлера
    float Yaw;
    float Pitch;
    // Настройки камеры
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;

    // Конструктор, использующий векторы
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);

    // Конструктор, использующие скаляры
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

    // Возвращает матрицу вида, вычисленную с использованием углов Эйлера и LookAt-матрицы
    glm::mat4 GetViewMatrix();

    //Обрабатываем входные данные, полученные от любой клавиатуроподобной системы ввода. Принимаем входной параметр
    //в виде определенного камерой перечисления (для абстрагирования его от оконных систем)
    void ProcessKeyboard(Camera_Movement direction, float deltaTime);

    //Обрабатываем входные данные, полученные от системы ввода с помощью мыши. Ожидаем в качестве параметров значения
    // смещения как в направлении X, так и в направлении Y.
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);

    // Обрабатывает входные данные, полученные от события колеса прокрутки мыши. Интересуют только входные данные
    // на вертикальную ось колесика
    void ProcessMouseScroll(float yoffset);

private:

    // Вычисляет вектор-прямо по (обновленным) углам Эйлера камеры
    void updateCameraVectors();

};

#endif //PROJECT_QUIZ_FIGURE_CAMERA_CLASS_H
