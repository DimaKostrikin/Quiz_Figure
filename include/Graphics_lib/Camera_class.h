#ifndef PROJECT_QUIZ_FIGURE_CAMERA_CLASS_H
#define PROJECT_QUIZ_FIGURE_CAMERA_CLASS_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>

#include <vector>
#include <map>

// Определяет несколько возможных вариантов движения камеры. Используется в качестве абстракции, чтобы держаться подальше от специфичных для оконной системы методов ввода
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Параметры камеры по умолчанию
const float YAW = -90.0f;
const float PITCH = 45.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

//Класс камеры, который обрабатывает входные данные и вычисляет соответствующие Эйлеровы углы, векторы и матрицы для использования в OpenGL
class Camera {
private:
    // Вычисляет вектор-прямо по (обновленным) углам Эйлера камеры
    void update_camera_vectors();
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
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.5f, 0.0f),
            glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW,
            float pitch = PITCH);

    // Конструктор, использующие скаляры
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw,
            float pitch);

    void set_yaw_pitch(float yaw = YAW, float pitch = PITCH);

    // Возвращает матрицу вида, вычисленную с использованием углов Эйлера и LookAt-матрицы
    glm::mat4 get_view_matrix();

    //Обрабатываем входные данные, полученные от любой клавиатуроподобной системы ввода. Принимаем входной параметр
    //в виде определенного камерой перечисления (для абстрагирования его от оконных систем)
    void process_keyboard(Camera_Movement direction, float deltaTime,  std::map <std::string, bool> control_tools);

    //Обрабатываем входные данные, полученные от системы ввода с помощью мыши. Ожидаем в качестве параметров значения
    // смещения как в направлении X, так и в направлении Y.
    void process_mouse_movement(float xoffset, float yoffset, GLboolean constrainPitch = true);

    // Обрабатывает входные данные, полученные от события колеса прокрутки мыши. Интересуют только входные данные
    // на вертикальную ось колесика
    void process_mouse_scroll(float yoffset);
};

#endif //PROJECT_QUIZ_FIGURE_CAMERA_CLASS_H
