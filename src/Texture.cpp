#include "Texture.hpp"
#include "stb_image.h"

#include <string>
#include <iostream>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#define GLCheck(x) GLClearErrors(); x; GLCheckErrorStatus(#x, __LINE__ );

static void GLClearErrors(){
    while(glGetError() != GL_NO_ERROR){
    }
}

static bool GLCheckErrorStatus(const char* function, int line){
    while(GLenum error = glGetError()){
        std::cout << "ERROR:" << error << "\nLINE:" << line << "\nFUNCTION:" << function <<std::endl;
        return true;
    }
    return false;
}

// Gets texture data with the given path
Texture::Texture(const char* findPath){
    int tWidth;
    int tHeight;
    int tNRChannels;
    stbi_set_flip_vertically_on_load(true);
    tData = stbi_load(findPath, &tWidth, &tHeight, &tNRChannels, 0);
    if(!tData){
        std::cout << "Error in texture1 loading" << std::endl;
        exit(1);
    }
}
        
// Binds a new texture object with the 
void Texture::bindTexture(GLuint* givenID){
    glGenTextures(1, givenID);
    glBindTexture(GL_TEXTURE_2D, *givenID);
    // Configures options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // Loads an generates texture
    GLCheck(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, tData);)
    glGenerateMipmap(GL_TEXTURE_2D);
}

// Frees data from the texture
void Texture::free(){
    stbi_image_free(tData);
}