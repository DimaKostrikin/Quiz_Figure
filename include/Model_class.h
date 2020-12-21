#ifndef PROJECT_QUIZ_FIGURE_MODEL_CLASS_H
#define PROJECT_QUIZ_FIGURE_MODEL_CLASS_H

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

#include <map>

#include "stb_image.h"

#include "Mesh_class.h"

#include "Shader.h"

#include "Events_manager.h"

unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);

class Model
{
public:
    Model(char *path);
    void Draw(Shader &shader, Camera camera, Events_manager ev_manager, bool is_light_source = false);
    void set_xpos(float xpos);
    void set_ypos(float ypos);
    void set_zpos(float zpos);
    void set_xscale(float xscale);
    void set_yscale(float yscale);
    void set_zscale(float zscale);
    void set_xangle(float xangle);
    void set_yangle(float yangle);
    void set_zangle(float zangle);

    float get_xpos();
    float get_ypos();
    float get_zpos();
    float get_xscale();
    float get_yscale();
    float get_zscale();
    float get_xangle();
    float get_yangle();
    float get_zangle();

private:

    // Данные модели
    std::vector<Texture> textures_loaded; // (оптимизация) сохраняем все загруженные текстуры, чтобы убедиться, что они не загружены более одного раза
    std::vector<Mesh> meshes;
    std::string directory;

    float _xpos = 0.f;
    float _ypos = 0.f;
    float _zpos = 0.f;
    float _xscale = 1.f;
    float _yscale = 1.f;
    float _zscale = 1.f;
    float _xangle = 0.f;
    float _yangle = 0.f;
    float _zangle = 0.f;

    void loadModel(std::string const &path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
};

#endif //PROJECT_QUIZ_FIGURE_MODEL_CLASS_H
