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
#include "Point_light.h"

class Model
{
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

    void load_model(std::string const &path);
    void process_node(aiNode *node, const aiScene *scene);
    Mesh process_mesh(aiMesh *mesh, const aiScene *scene);
    std::vector<Texture> load_material_textures(aiMaterial *mat, aiTextureType type, std::string typeName);
public:
    Model(char *path);
    void draw(Shader &shader, Camera camera, std::map <std::string, bool> control_tools, std::vector <Point_light> point_lights, bool is_light_source = false);
    unsigned int texture_from_file(const char *path, const std::string &directory, bool gamma = false);
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
};

#endif //PROJECT_QUIZ_FIGURE_MODEL_CLASS_H
