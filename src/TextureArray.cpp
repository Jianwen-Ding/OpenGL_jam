#include "string"
#include "Texture.hpp"
#include "TextureArray.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glad/glad.h>

TextureArray::TextureArray(std::vector<Texture> textures, GLenum givenFormat, GLsizei width, GLsizei height){
    // Creates a texture array
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D_ARRAY, ID);

    // Set Array Storage
    glTexStorage3D(GL_TEXTURE_2D_ARRAY, 1, givenFormat, width, height, textures.size());

    // 
}