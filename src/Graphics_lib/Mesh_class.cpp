#include "Graphics_lib/Mesh_class.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
{
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;

    setup_mesh();
}

void Mesh::setup_mesh()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
                 &indices[0], GL_STATIC_DRAW);

    // Координаты вершин
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

    // Нормали вершин
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

    // Текстурные координаты вершин
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

    glBindVertexArray(0);
}

void Mesh::draw(Shader shader, Camera camera, std::map <std::string, bool> control_tools, std::vector <Point_light> point_lights, bool is_light_source)
{

    glm::vec3 pointLightPositions[] = {
            glm::vec3( -3.0f,  1.0f,  5.0f),
            glm::vec3( -5.0f, 1.0f, 5.0f),
            glm::vec3(-5.0f,  1.0f, 3.0f),
            glm::vec3( -5.0f,  1.0f, 1.0f)
    };

    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    for(unsigned int i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i); // активируем соответствующий текстурный юнит перед привязкой
        // Получаем номер текстуры (значение N в diffuse_textureN)
        std::string number;
        std::string name = textures[i].type;
        if(name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if(name == "texture_specular")
            number = std::to_string(specularNr++);

        shader.setFloat(("material." + name + number).c_str(), i);
        shader.setFloat("material.shininess", 128.0f);
        shader.setInt("material.specular", 1);

        // направленный свет
        if (is_light_source) shader.setVec3("dirLight.ambient", 1.0f, 1.0f, 1.0f);
        else shader.setVec3("dirLight.ambient", 0.5f, 0.5f, 0.5f);

        shader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
        shader.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
        shader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);

        shader.setInt("pointLightsAmount", point_lights.size());

        for (size_t i = 0; i < point_lights.size(); ++i) {
            shader.setVec3(("pointLights["+ std::to_string(i) + "].position").c_str(), point_lights[i].get_position());
            shader.setVec3(("pointLights[" + std::to_string(i) + "].ambient").c_str(), point_lights[i].get_ambient());
            shader.setVec3(("pointLights[" + std::to_string(i) + "].diffuse").c_str(), point_lights[i].get_diffuse());
            shader.setVec3(("pointLights[" + std::to_string(i) + "].specular").c_str(), point_lights[i].get_specular());
            shader.setFloat(("pointLights[" + std::to_string(i) + "].constant").c_str(), point_lights[i].get_constant());
            shader.setFloat(("pointLights[" + std::to_string(i) + "].linear").c_str(), point_lights[i].get_linear());
            shader.setFloat(("pointLights[" + std::to_string(i) + "].quadratic").c_str(), point_lights[i].get_quadratic());
        }

        // прожектор(фонарик)
        if (control_tools["Flashlight"]) {
            shader.setBool("spotLight.active", 1);
            shader.setVec3("spotLight.position", camera.Position);
            shader.setVec3("spotLight.direction", camera.Front);
            shader.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
            shader.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
            shader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
            shader.setFloat("spotLight.constant", 1.0f);
            shader.setFloat("spotLight.linear", 0.09);
            shader.setFloat("spotLight.quadratic", 0.032);
            shader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
            shader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));
        }
        else shader.setBool("spotLight.active", 0);

        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }
    glActiveTexture(GL_TEXTURE0);

    // Отрисовываем меш
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

