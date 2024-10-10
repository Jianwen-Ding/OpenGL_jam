#ifndef TEXTUREARRAY_HPP
#define TEXTUREARRAY_HPP

#include "string"
#include "Texture.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glad/glad.h>

class TextureArray{
    public:
        GLuint ID;
        TextureArray(std::vector<Texture> textures, GLenum givenFormat, GLsizei width, GLsizei height);
};

#endif