#ifndef MODEL_HPP
#define MODEL_HPP

#include "Transform.hpp"
#include "Shader.hpp"
#include "Mesh.hpp"
#include "string"

#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model{
    public:
        Model(char *path, char *setBase);
        void Draw(Shader &shader, Transform &transform);
    private:
        std::vector<Mesh> meshes;
        std::vector<Texture> textures_loaded;
        std::string dir;
        std::string base;

        void loadModel(std::string path);
        void processNode(aiNode *node, const aiScene *scene);
        Mesh processMesh(aiMesh *mesh, const aiScene *scene);
        std::vector<Texture> loadMaterial(aiMaterial *mat, aiTextureType type, std::string typeName);
};
#endif