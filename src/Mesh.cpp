#include "Mesh.hpp"
#include "Shader.hpp"
#include "TextureArray.hpp"
#include "Vertex.hpp"

#include <iostream>
#include <string>
#include <glm/glm.hpp>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glad/glad.h>


#define GLCheck(x) GLClearErrors(); x; GLCheckErrorStatus(#x, __LINE__ );

static void GLClearErrors(){
    while(glGetError() != GL_NO_ERROR){
    }
}

static bool GLCheckErrorStatus(const char* function, int line){
    GLenum error;
    while ((error = glGetError()) != GL_NO_ERROR) {
        std::cout << "OpenGL error in " << function << " at line " << line << ": ";
        switch (error) {
            case GL_INVALID_ENUM:
                std::cout << "GL_INVALID_ENUM\n";
                break;
            case GL_INVALID_VALUE:
                std::cout << "GL_INVALID_VALUE\n";
                break;
            case GL_INVALID_OPERATION:
                std::cout << "GL_INVALID_OPERATION\n";
                break;
            case GL_OUT_OF_MEMORY:
                std::cout << "GL_OUT_OF_MEMORY\n";
                break;
            default:
                std::cout << "Unknown error\n";
                break;
        }
        return true;
    }
    return false;
}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, TextureArray* textures){
    this -> vertices = vertices;
    this -> indices = indices;
    this -> textures = textures;
    
    GLCheck(setupMesh();)
}

Mesh::~Mesh(){
    // glDeleteVertexArrays(1, &VAO);
    // glDeleteBuffers(1, &VBO);
    // glDeleteBuffers(1, &EBO);
}

void Mesh::Draw(Shader &shader){
    shader.setInt("u_textureLength", textures->uvVectors.size());
    shader.setVec2List("u_uvCoords", textures->uvVectors.size(), textures->uvVectors);
    shader.setInt("u_specBarrier", textures->specBarrier);

    // Assign texture
    GLCheck(glActiveTexture(GL_TEXTURE0);)
    GLCheck(glBindTexture(GL_TEXTURE_2D_ARRAY, textures->ID);)

    // Draw mesh
    glBindVertexArray(VAO);
    // std::cout << "indices " << indices.size() << std::endl;
    glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);
    GLCheck(glBindVertexArray(0);)
}

void  Mesh::setupMesh(){
    // Binds Mesh Objects
    GLCheck(glGenVertexArrays(1, &VAO);)
    GLCheck(glGenBuffers(1, &VBO);)
    GLCheck(glGenBuffers(1, &EBO);)

    GLCheck(glBindVertexArray(VAO);)
    GLCheck(glBindBuffer(GL_ARRAY_BUFFER, VBO);)

    GLCheck(glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);)

    GLCheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);)
    GLCheck(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);)

    // Vertex position
    GLCheck(glEnableVertexAttribArray(0);)
    GLCheck(glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE,sizeof(Vertex), (void*)0);)
    // Vertex normals
    GLCheck(glEnableVertexAttribArray(1);)
    GLCheck(glVertexAttribPointer(1,3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));)
    // Vetex texture coords
    GLCheck(glEnableVertexAttribArray(2);)
    GLCheck(glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));)

    GLCheck(glBindVertexArray(0);)
}