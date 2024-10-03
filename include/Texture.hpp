#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "string"
#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"

struct Texture{
    public:
        unsigned int id;
        std::string type;
        Texture(unsigned int setId, std::string setType);
};
#endif
