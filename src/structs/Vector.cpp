#include "Vertex.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"

Vertex::Vertex(glm::vec3 PositionSet, glm::vec3 NormalSet, glm::vec2 TexCoordsSet){
    Position = PositionSet;
    Normal = NormalSet;
    TexCoords = TexCoordsSet;
}