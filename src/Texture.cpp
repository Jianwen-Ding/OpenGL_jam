#include "Texture.hpp"
#include "stb_image.h"

#include <string>
#include <iostream>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <filesystem>

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
Texture::Texture(const char* findPath, bool flipOnLoad){
    stbi_set_flip_vertically_on_load(flipOnLoad);

    tData = stbi_load(findPath, &tWidth, &tHeight, &tNRChannels, 0);
    if(stbi_failure_reason()){
        std::cout << stbi_failure_reason() << std::endl;
    }
    if(!(*tData)){
        std::cout << "Error in texture loading" << std::endl;
    }
    tPath = findPath;
}

// Plugs in texture data directly
Texture::Texture(unsigned char* givenData, int givenWidth, int givenHeight, int setNRChannels){
    tData = givenData;
    tWidth = givenWidth;
    tHeight = givenHeight;
    tNRChannels = setNRChannels;
    tPath = "-None-";
}

// Binds a new texture object with the 
void Texture::bindTexture(GLuint* givenID){
    switch(tNRChannels){
        case 1:
            tFormat = GL_RED;
            break;
        case 3:
            tFormat = GL_RGB;
            break;
        case 4:
            tFormat = GL_RGBA;
            break;
        default:
            std::cout << "ERROR::UNACCOUNTED NR CHANNELS" << std::endl;
            exit(1);
    }
    glGenTextures(1, givenID);
    glBindTexture(GL_TEXTURE_2D, *givenID);
    // Configures options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // Loads an generates texture
    GLCheck(glTexImage2D(GL_TEXTURE_2D, 0, tFormat, tWidth, tHeight, 0, tFormat, GL_UNSIGNED_BYTE, tData);)
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(tData);
}

// Frees data from the texture
void Texture::free(){
    stbi_image_free(tData);
}