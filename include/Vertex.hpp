#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

struct Vertex{
    public:
        glm::vec3 Position;
        glm::vec3 Normal;
        glm::vec2 TexCoords;
        Vertex(glm::vec3 PositionSet, glm::vec3 NormalSet, glm::vec2 TexCoordsSet);
};
#endif
