#ifndef PROJECT_QUIZ_FIGURE_MODEL_H
#define PROJECT_QUIZ_FIGURE_MODEL_H

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

#include "stb_image.h"

#include "Mesh_class.h"

#include "Shader.h"

unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);

class Model
{
public:
    Model(char *path);
    void Draw(Shader &shader, Camera camera);
private:

    // Данные модели
    std::vector<Texture> textures_loaded; // (оптимизация) сохраняем все загруженные текстуры, чтобы убедиться, что они не загружены более одного раза
    std::vector<Mesh> meshes;
    std::string directory;

    void loadModel(std::string const &path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
};

#endif //PROJECT_QUIZ_FIGURE_MODEL_H
