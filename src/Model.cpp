#include "Model.hpp"
#include "Shader.hpp"
#include "Mesh.hpp"
#include "string"
#include "Texture.hpp"
#include "TextureArray.hpp"
#include "stb_image.h"

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

Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene){
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::vector<Texture> textures;
    // Gets vertices
    for(unsigned int i = 0; i < mesh->mNumVertices; i++){
        // Finds position of vertex
        glm::vec3 posVec;
        posVec.x = mesh->mVertices[i].x;
        posVec.y = mesh->mVertices[i].y;
        posVec.z = mesh->mVertices[i].z;
        
        // Finds normals of vertex
        glm::vec3 normVec;
        normVec.x = mesh->mNormals[i].x;
        normVec.y = mesh->mNormals[i].y;
        normVec.z = mesh->mNormals[i].z;

        glm::vec2 uvVec;
        // Finds texture coords of vertex
        if(mesh->mTextureCoords[0]){
            uvVec.x = mesh->mTextureCoords[0][i].x;
            uvVec.y = mesh->mTextureCoords[0][i].y;
        }
        else{
            uvVec = glm::vec2(0.0f, 0.0f);
        }
        Vertex vert = *(new Vertex(posVec, normVec, uvVec));
        vertices.push_back(vert);
    }

    // Gets indices
    for(unsigned int i = 0; i < mesh->mNumFaces; i++){
        aiFace face = mesh->mFaces[i];
        for(unsigned int j = 0; j < face.mNumIndices; j++){
            indices.push_back(face.mIndices[j]);
        }
    }

    // Gets Textures
    if(mesh->mMaterialIndex >= 0){
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
        std::vector<Texture> diffuseMaps = loadMaterial(material, aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    }

    TextureArray* givenArray = new TextureArray(textures);
    return Mesh(vertices, indices, givenArray);
}

std::vector<Texture> Model::loadMaterial(aiMaterial *mat, aiTextureType type, std::string typeName){
    std::vector<Texture> textures;
    for(unsigned int i = 0; i < mat->GetTextureCount(type); i++){
        aiString str;
        mat->GetTexture(type,i,&str);
        Texture texture = Texture(str.C_Str());
        textures.push_back(texture);
    }
    return textures;
}