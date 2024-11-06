#include "Transform.hpp"

#include <iostream>
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
    if(parent == nullptr){
        return modelMatrix;
    }
    return modelMatrix * parent->getTransformMat();
}

Transform::Transform(){
    parent = nullptr;
    scale = glm::vec3(1.0f);
    position = glm::vec3(0.0f);
    rotation = glm::quat(1.0f, 0, 0, 0);
}

Transform::Transform(glm::vec3 setScale, glm::vec3 setPositon, glm::quat setRotation){
    parent = nullptr;
    scale = setScale;
    position = setPositon;
    rotation = setRotation;
}

glm::vec3 Transform::getFoward(){
    if(parent == nullptr){
        return rotation * glm::vec3(0.0f,0.0f, -1.0f);
    }
    return (parent->rotation * rotation) * glm::vec3(0.0f,0.0f, -1.0f);
}

void Transform::setParent(Transform* setParent){
    // Checks if parent ever loops back to itself
    Transform* iterParent = setParent;
    bool containsSelf = false;
    while(iterParent != nullptr){
        if(iterParent == this){
            containsSelf = true;
            std::cout << "attempted to set transform to parent of itself" << std::endl;
            break;
        }
        iterParent = iterParent->parent;
    }
    if(!containsSelf){
        parent = setParent;
    }
}