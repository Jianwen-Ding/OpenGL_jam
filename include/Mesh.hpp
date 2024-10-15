#ifndef MESH_HPP
#define MESH_HPP

#include "Vertex.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "TextureArray.hpp"
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

class Mesh {
    public:
        // mesh data
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        TextureArray* textures;

        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, TextureArray* textures);
        void Draw(Shader &shader);
    private:
        //  render data
        unsigned int VAO, VBO, EBO;

        void setupMesh();
};  
#endif
