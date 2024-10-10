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

        // Dimensions of the texture
        int tWidth;
        int tHeight;
        int tNRChannels;

        // Creates texture with the given path
        Texture(const char* findPath);

        // Binds a new texture object with the 
        void bindTexture(GLuint* givenID);

        // Frees the data imbued within the Texture
        void free();
};
#endif
