#ifndef PROJECT_QUIZ_FIGURE_MESH_CLASS_H
#define PROJECT_QUIZ_FIGURE_MESH_CLASS_H

#include <cstddef>
#include <map>

#include "Camera_class.h"
#include "Shader.h"
#include "Events_manager.h"

struct Vertex {

    // Позиция
    glm::vec3 Position;
    // Нормаль
    glm::vec3 Normal;
    // Текстурные координаты
    glm::vec2 TexCoords;
    // Касательный вектор
    glm::vec3 Tangent;
    // Вектор бинормали (вектор, перпендикулярный касательному вектору и вектору нормали)
    glm::vec3 Bitangent;
};

struct Texture {
    unsigned int id;
    std::string type;
    std::string path; // мы сохраняем путь к текстуре, чтобы сравнивать с другими текстурами

};

class Mesh {
public:
    // mesh-данные
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
    void Draw(Shader shader, Camera camera, Events_manager ev_manager, bool is_light_source = false);
private:
    // Данные для рендеринга
    unsigned int VAO, VBO, EBO;

    void setupMesh();
};

#endif //PROJECT_QUIZ_FIGURE_MESH_CLASS_H
