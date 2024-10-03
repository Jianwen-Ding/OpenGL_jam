#ifndef MESH_HPP
#define MESH_HPP

#include "Vertex.hpp";
#include "vector";
#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"

class Mesh {
    public:
        // mesh data
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture> textures;

        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
        void Draw(Shader &shader);
    private:
        //  render data
        unsigned int VAO, VBO, EBO;

        void setupMesh();
};  
#endif
