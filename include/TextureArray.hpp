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
        std::vector<glm::vec2> uvVectors;
        TextureArray(std::vector<Texture> textures, GLenum format);
        TextureArray(std::vector<Texture> textures, GLsizei width, GLsizei height, GLenum format);
    private:
        void constructWithData(std::vector<Texture> data, GLsizei width, GLsizei height, GLenum format);
        unsigned char* padTexture(unsigned char* data, GLsizei ogWidth, GLsizei ogHeight, GLsizei newWidth, GLsizei newHeight, int stride, int orgStride);
};

#endif