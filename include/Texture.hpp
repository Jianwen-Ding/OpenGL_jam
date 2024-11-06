#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "string"
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glad/glad.h>

// Stores data from texture itself, to be created an quickly let go
class Texture{
    public:
        // Data of texture itself
        unsigned char *tData;
        GLenum tFormat;

        // Dimensions of the texture
        int tWidth;
        int tHeight;
        int tNRChannels;

        // Path to identify texture
        std::string tPath;

        // Creates texture with the given path
        Texture(const char* findPath);

        // Creates texture with given information
        Texture(unsigned char* givenData, int givenWidth, int givenHeight, int setNRChannels);
        
        // Binds a new texture object with the 
        void bindTexture(GLuint* givenID);

        // Frees the data imbued within the Texture
        void free();
};
#endif
