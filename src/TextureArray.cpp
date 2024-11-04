#include "string"
#include "Texture.hpp"
#include "TextureArray.hpp"
#include "stb_image.h"

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glad/glad.h>
#define GLCheck(x) GLClearErrors(); x; GLCheckErrorStatus(#x, __LINE__ );

static void GLClearErrors(){
    while(glGetError() != GL_NO_ERROR){
    }
}

static bool GLCheckErrorStatus(const char* function, int line){
    GLenum error;
    while ((error = glGetError()) != GL_NO_ERROR) {
        std::cout << "OpenGL error in " << function << " at line " << line << ": ";
        switch (error) {
            case GL_INVALID_ENUM:
                std::cout << "GL_INVALID_ENUM\n";
                break;
            case GL_INVALID_VALUE:
                std::cout << "GL_INVALID_VALUE\n";
                break;
            case GL_INVALID_OPERATION:
                std::cout << "GL_INVALID_OPERATION\n";
                break;
            case GL_OUT_OF_MEMORY:
                std::cout << "GL_OUT_OF_MEMORY\n";
                break;
            default:
                std::cout << "Unknown error\n";
                break;
        }
        return true;
    }
    return false;
}

// Creates texture with direct data assumes that all textures have the same size
void TextureArray::constructWithData(std::vector<Texture> textures, GLsizei width, GLsizei height, GLenum format){
    GLenum mainFormat;
    GLenum subFormat;
    int stride;

    subFormat = format;
    switch(format){
        case GL_RED:
            mainFormat = GL_R8;
            stride = 1;
            break;
        case GL_RGB:
            mainFormat = GL_RGB8;
            stride = 3;
            break;
        case GL_RGBA:
            mainFormat = GL_RGBA8;
            stride = 4;
            break;
        default:
            std::cout << "ERROR INVALID FORMAT GIVEN" << std::endl;
            exit(1);
    }

    // Creates a texture array
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D_ARRAY, ID);

    // Set Array Storage
    std::cout << textures.size() << std::endl;
    GLCheck(glTexStorage3D(GL_TEXTURE_2D_ARRAY, 1, mainFormat, width, height, textures.size());)

    // Loops throug the given textures
    for(int i = 0; i < textures.size(); i++){
        glm::vec2 givenUV;
        GLsizei textureWidth = textures[i].tWidth;
        GLsizei textureHeight = textures[i].tHeight;
        // Gets width ratio
        givenUV.x = 1;
        if(width != textureWidth){
            givenUV.x = (float)textureWidth/(float)width;
        }
        // Gets height ratio
        givenUV.y = 1;
        if(height != textureHeight){
            givenUV.y = (float)textureHeight/(float)height;
        }
        uvVectors.push_back(givenUV);
        // Actually pads texture data
        unsigned char* paddedData = padTexture(textures[i].tData, textures[i].tWidth, textures[i].tHeight, width, height, stride, textures[i].tNRChannels);
        GLCheck(glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, i, width, height, 1, subFormat, GL_UNSIGNED_BYTE, paddedData);)
        stbi_image_free(paddedData);
    }

    // Load options
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glGenerateMipmap(GL_TEXTURE_2D_ARRAY);
}

// Pads texture
unsigned char* TextureArray::padTexture(unsigned char* data, GLsizei ogWidth, GLsizei ogHeight, GLsizei newWidth, GLsizei newHeight, int stride, int orgStride){

    // fills return data with empty
    unsigned char* retData = new unsigned char[stride * newWidth * newHeight];
    for(int i = 0; i < stride * newWidth * newHeight; i++){
        retData[i] = 0;
    }

    // fills return data with given data
    for(int y = 0; y < ogHeight; y++){
        for(int x = 0; x < ogWidth; x++){
            int retDataIdx = y * newWidth * stride + x * stride;
            int orgIdx = y * ogWidth * orgStride + x * orgStride;
            
            // Copies data over depending on given stride
            for(int i = 0; i < stride; i++){
                retData[retDataIdx + i] = data[orgIdx + i];
            }
        }
    }
    return retData;
}
// Creates a texture array with a set size
TextureArray::TextureArray(std::vector<Texture> textures, GLsizei width, GLsizei height, GLenum format){
    // Assumes that all textures are diffusion at first
    specBarrier = textures.size();
    // Plugs texture data into array while checking to make sure texture works
    std::vector<unsigned char*> dataGiven;
    for(int i = 0; i < textures.size(); i++){
        if(width > textures[i].tWidth || height > textures[i].tHeight){
            std::cout << "Invalid width/height give" << std::endl;
            exit(1);
        }
    }
    TextureArray::constructWithData(textures, width, height, format);
}

TextureArray::TextureArray(std::vector<Texture> textures, GLenum format){
    // Assumes that all textures are diffusion at first
    specBarrier = textures.size();
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
    TextureArray::constructWithData(textures, maxWidth, maxHeight, format);
}