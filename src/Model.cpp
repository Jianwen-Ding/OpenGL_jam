#include "Model.hpp"
#include "Shader.hpp"
#include "Mesh.hpp"
#include "string"

#include <vector>
#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

void Model::Draw(Shader &shader){
    for(unsigned int i = 0; i < meshes.size(); i++){
        meshes[i].Draw(shader);
    }
}

Model::Model(char *path){
    Model::loadModel(path);
}

void Model::loadModel(std::string path){
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode){
        std::cout << "ERROR::ASSIMP::" <<  importer.GetErrorString() << std::endl;
        exit(1);
    }
    dir = path.substr(0, path.find_last_of('/'));

    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode *node, const aiScene *scene){
    for(unsigned int i = 0; i < node->mNumMeshes;i++){
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh,scene));
    }
    for(unsigned int i = 0; i < node->mNumChildren;i++){
        processNode(node->mChildren[i], scene);
    }
}

Mesh processMesh(aiMesh *mesh, const aiScene *scene){
    
}
