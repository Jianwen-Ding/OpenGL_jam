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
    if(hasParent){
        return parent->getTransformMat() * modelMatrix;
    }
    else{
        return modelMatrix;
    }
}

Transform::Transform(){
    hasParent = false;
    parent = nullptr;
    scale = glm::vec3(1.0f);
    position = glm::vec3(0.0f);
    rotation = glm::quat(1.0f, 0, 0, 0);
}

Transform::Transform(glm::vec3 setScale, glm::vec3 setPositon, glm::quat setRotation){
    hasParent = false;
    parent = nullptr;
    scale = setScale;
    position = setPositon;
    rotation = setRotation;
}

glm::vec3 Transform::getFoward(){
    if(hasParent){
        return (parent->rotation * rotation) * glm::vec3(0.0f,0.0f, -1.0f);  
    }
    else{
        return rotation * glm::vec3(0.0f,0.0f, -1.0f);   
    }
}

void Transform::setParent(Transform* set){
    Transform* iter = set;
    bool constainsSelf = false;
    while(iter != nullptr){
        if(iter == this){
            std::cout << "Transform attempted to become parent of itself" << std::endl;
            constainsSelf = true;
        }
        iter = iter->parent;
    }
    if(!constainsSelf){
        parent = set;
    }
}