#include "string"
#include "Texture.hpp"
#include "TextureArray.hpp"

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glad/glad.h>

// Creates texture with direct data assumes that all textures have the same size
void TextureArray::constructWithData(std::vector<unsigned char*> textures, GLenum givenFormat, GLsizei width, GLsizei height){
    // Creates a texture array
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D_ARRAY, ID);

    // Load options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Set Array Storage
    glTexStorage3D(GL_TEXTURE_2D_ARRAY, 1, givenFormat, width, height, textures.size());

    // Loops throug the given textures
    for(int i = 0; i < textures.size(); i++){
        glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, i, width, height, 1, GL_RGBA, GL_UNSIGNED_BYTE, textures[i]);
    }
    
    glGenerateMipmap(GL_TEXTURE_2D_ARRAY);
}


TextureArray::TextureArray(std::vector<unsigned char*> textures, GLenum givenFormat, GLsizei width, GLsizei height){
    TextureArray::constructWithData(textures, givenFormat, width, height);
}

// Creates a texture array with a set size
TextureArray::TextureArray(std::vector<Texture> textures, GLenum givenFormat, GLsizei width, GLsizei height){
    // Plugs texture data into array while checking to make sure texture works
    std::vector<unsigned char*> dataGiven;
    for(int i = 0; i < textures.size(); i++){
        if(width > textures[i].tWidth || height > textures[i].tHeight){
             std::cout << "Invalid width/height give" << std::endl;
            exit(1);
        }
        dataGiven.push_back(textures[i].tData);
    }
    TextureArray::constructWithData(dataGiven, givenFormat, width, height);
}

TextureArray::TextureArray(std::vector<Texture> textures, GLenum givenFormat){
    std::vector<unsigned char*> dataGiven;
    int maxWidth = 1;
    int maxHeight = 1;
    for(int i = 0; i < textures.size(); i++){
        if(maxHeight < textures[i].tHeight){
            maxHeight = textures[i].tHeight;
        }
        if(maxWidth < textures[i].tWidth){
            maxWidth = textures[i].tWidth;
        }
        dataGiven.push_back(textures[i].tData);
    }
    TextureArray::constructWithData(dataGiven, givenFormat, maxWidth, maxHeight);
}