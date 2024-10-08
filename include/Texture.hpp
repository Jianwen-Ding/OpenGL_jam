#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "string"
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glad/glad.h>

struct Texture{
    public:
        GLuint id;
        std::string type;
        Texture(unsigned int setId, std::string setType);
};
#endif
