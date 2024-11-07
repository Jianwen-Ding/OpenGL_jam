#include "Plane.hpp"

#include <iostream>

Plane::Plane(Camera* setCamera, RenderManager* manager, int planeModelIdx, float setVeer, float setDrag, float setGravity, float setAccel, float setLift, float setMaxVel, glm::vec3 initPos) : 
givenCamera(setCamera),
renderManager(manager),
veerSpeed(setVeer),
drag(setDrag),
gravity(setGravity),
acceleration(setAccel),
lift(setLift),
maxVel(setMaxVel){
    mainTransform = Transform(glm::vec3(0.5f), initPos, glm::normalize(glm::quat(1.0f, 0.0f, 0.0f, 0.0f)));
    cameraTransform = Transform(glm::vec3(0.5f), glm::vec3(0.0f, 2.5f, -15.0f), glm::normalize(glm::quat(0.0f, 0.0f, -1.0f, 0.0f)));
    cameraTransform.setParent(&mainTransform);
    spotlightTransform = Transform(glm::vec3(0.5f), glm::vec3(0.0f, 0.0f, 5.0f), glm::normalize(glm::quat(1.0f, 0.0f, 0.0f, 0.0f)));
    spotlightTransform.setParent(&mainTransform);
    ModelObject* createdModel = new ModelObject(&mainTransform, planeModelIdx, manager);
    currentModel.reset(createdModel);
    currentLight.reset(nullptr);
}

// Changes direction to veer plane into
void Plane::veerLeft(float deltaTime){
    mainTransform.rotation = glm::normalize(glm::quat(1.0f, deltaTime * veerSpeed, 0.0f, 0.0f)) * mainTransform.rotation;
}

// Changes direction to veer plane into
void Plane::veerRight(float deltaTime){
    mainTransform.rotation = glm::normalize(glm::quat(1.0f, -deltaTime * veerSpeed, 0.0f, 0.0f)) * mainTransform.rotation;
}

// Changes direction to veer plane into
void Plane::veerUp(float deltaTime){
    mainTransform.rotation = glm::normalize(glm::quat(1.0f, 0.0f, 0.0f, deltaTime * veerSpeed)) * mainTransform.rotation;
}

// Changes direction to veer plane into
void Plane::veerDown(float deltaTime){
    mainTransform.rotation = glm::normalize(glm::quat(1.0f, 0.0f, 0.0f, -deltaTime * veerSpeed)) * mainTransform.rotation;
}

// Accelerates the plane forwards
void Plane::accel(float deltaTime){
    velocity += deltaTime * acceleration * mainTransform.getFoward();
}

// Causes light 
void Plane::fireLights(){
    if(currentLight == nullptr){
        currentLight.reset(
            new SpotLightObject(&spotlightTransform , renderManager, glm::vec3(0.1f),glm::vec3(0.5f),glm::vec3(0.2f), glm::cos(glm::radians(12.5f)), glm::cos(glm::radians(17.5f)), 1.0f, 0.09, 0.032));
    }
}

void Plane::deactivateLights(){
    currentLight.reset(nullptr);
}

// Updates the planes physics
void Plane::update(float deltaTime){
    mainTransform.position += velocity * deltaTime;
    givenCamera->setEyeLoc(cameraTransform.getWorldPosition());
    givenCamera->setViewOrient(cameraTransform.getWorldRotation());

    velocity -= deltaTime * gravity * glm::vec3(0.0f,-1.0f, 0.0f); 
    velocity += deltaTime * lift * (glm::vec3(0.0f,1.0f, 0.0f) * mainTransform.rotation);
    velocity -= deltaTime * drag * velocity;
    std::cout << "(" << mainTransform.position.x << "," << mainTransform.position.y << "," << mainTransform.position.z << ")" << std::endl;
}