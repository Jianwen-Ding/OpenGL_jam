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
    if(parent != nullptr){
        return  modelMatrix * parent->getTransformMat();
    }
    return modelMatrix;
}

Transform::Transform(){
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
    return getWorldRotation() * glm::vec3(0.0f,0.0f, -1.0f);
}

void Transform::setParent(Transform* setParent){
    Transform* transformIter = setParent;
    bool containsSelf = false;
    while(transformIter != nullptr){
        if(transformIter == this){
            containsSelf = true;
            std::cout << "Attempted to set to parent of itself" << std::endl;
            break;
        }
        transformIter = transformIter->parent;
    }
    if(!containsSelf){
        parent = setParent;
    }
}

glm::vec3 Transform::getWorldScale(){
    if(parent != nullptr){
        return (parent->getWorldScale() * scale);
    }
    return scale;
}

glm::vec3 Transform::getWorldPosition(){
    if(parent != nullptr){
        return glm::vec3(parent->getTransformMat() * glm::vec4(position,1.0f));
    }
    return position;
}

glm::quat Transform::getWorldRotation(){
    if(parent != nullptr){
        return (parent->getWorldRotation() * rotation);
    }
    return rotation;
}