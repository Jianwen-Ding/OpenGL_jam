#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glad/glad.h>

class Transform{
    public:
        glm::vec3 scale;
        glm::vec3 position;
        glm::quat rotation;
        std::vector<Transform*> parents;
        glm::mat4 getTransformMat();
        Transform();
        Transform(glm::vec3 setScale, glm::vec3 setPosition, glm::quat getRotation);

        glm::vec3 getFoward();
};

#endif