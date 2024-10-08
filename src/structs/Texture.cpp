#include "Texture.hpp"

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

Texture::Texture(GLuint setId, std::string setType){
    id = setId;
    type = setType;
}