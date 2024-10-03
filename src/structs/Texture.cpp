#include "Texture.hpp"

#include "string"
#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"

Texture::Texture(unsigned int setId, std::string setType){
    id = setId;
    type = setType;
}