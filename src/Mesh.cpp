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

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, TextureArray* textures){
    this -> vertices = vertices;
    this -> indices = indices;
    this -> textures = textures;

    setupMesh();
}

void Mesh::Draw(Shader &shader){
    shader.use();
    
    shader.setInt("u_textureLength", textures->uvVectors.size());
    shader.setVec2List("u_uvCoords", textures->uvVectors.size(), textures->uvVectors);

    // Assign texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D_ARRAY, textures->ID);

    // Draw mesh
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void  Mesh::setupMesh(){
    // Binds Mesh Objects
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

    // Vertex position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE,sizeof(Vertex), (void*)0);
    // Vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    // Vetex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

    glBindVertexArray(0);
}