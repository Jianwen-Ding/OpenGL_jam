#include "Transform.hpp"

#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

glm::mat4 Transform::getTransformMat(){
    glm::mat4 modelMatrix= glm::mat4x4(1.0f);
    modelMatrix = glm::translate(modelMatrix, position);
    modelMatrix = modelMatrix * glm::mat4_cast(rotation);
    modelMatrix = glm::scale(modelMatrix, scale);
    return modelMatrix;
}

Transform::Transform(){
    scale = glm::vec3(1.0f);
    position = glm::vec3(0.0f);
    rotation = glm::quat(1.0f, 0, 0, 0);
}

Transform::Transform(glm::vec3 setScale, glm::vec3 setPositon, glm::quat setRotation){
    scale = setScale;
    position = setPositon;
    rotation = setRotation;
}