#ifndef MODEL_HPP
#define MODEL_HPP

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
        void Draw(Shader &shader);
    private:
        std::vector<Mesh> meshes;
        std::string dir;
        std::string base;

        void loadModel(std::string path);
        void processNode(aiNode *node, const aiScene *scene);
        Mesh processMesh(aiMesh *mesh, const aiScene *scene);
        std::vector<Texture> loadMaterial(aiMaterial *mat, aiTextureType type, std::string typeName);
};
#endif