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
        TextureArray(std::vector<Texture> textures, std::vector<glm::vec2>* textureUV);
        TextureArray(std::vector<Texture> textures, GLsizei width, GLsizei height, std::vector<glm::vec2>* textureUV);
    private:
        void constructWithData(std::vector<Texture> data, GLsizei width, GLsizei height, std::vector<glm::vec2>* textureUV);
        unsigned char* padTexture(unsigned char* data, GLsizei ogWidth, GLsizei ogHeight, GLsizei newWidth, GLsizei newHeight);
};

#endif