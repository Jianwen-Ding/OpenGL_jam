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
maxVel(setMaxVel),
mainTransform(glm::vec3(0.05f), initPos, glm::normalize(glm::quat(1.0f, 0.0f, 0.0f, 0.0f))),
cameraTransform(glm::vec3(0.5f), glm::vec3(0.0f, 3.0f, -20.0f), glm::normalize(glm::quat(0.0f, 0.0f, -1.0f, 0.0f))),
spotlightTransform(glm::vec3(0.5f), glm::vec3(0.0f, 0.0f, 15.0f), glm::normalize(glm::quat(0.0f, 0.0f, -1.0f, 0.0f))),
velocity(glm::vec3(0.0f)){
    cameraTransform.setParent(&mainTransform);
    spotlightTransform.setParent(&mainTransform);
    ModelObject* createdModel = new ModelObject(&mainTransform, planeModelIdx, manager);
    currentModel.reset(createdModel);
    currentLight.reset(nullptr);
}

void Plane::veerMouse(float deltaTime, float mouseX, float mouseY){
    glm::vec2 currentMouse = glm::vec2(mouseX,mouseY);
    glm::quat yRot = glm::normalize(glm::quat(cos(-currentMouse.y/200),sin(-currentMouse.y/200),0,0));
    glm::quat xRot = glm::normalize(glm::quat(cos(-currentMouse.x/200),0,sin(-currentMouse.x/200),0));
    mainTransform.rotation = mainTransform.rotation * xRot * yRot;
}
// Changes direction to veer plane into
void Plane::veerLeft(float deltaTime){
    float veerAmount = deltaTime * veerSpeed;
    glm::quat veerQuat = glm::angleAxis(veerAmount, glm::vec3(0.0f, 1.0f, 0.0f));
    mainTransform.rotation = glm::normalize(veerQuat * mainTransform.rotation);
}

// Changes direction to veer plane into
void Plane::veerRight(float deltaTime){
    float veerAmount = deltaTime * veerSpeed;
    glm::quat veerQuat = glm::angleAxis(-veerAmount, glm::vec3(0.0f, 1.0f, 0.0f));
    mainTransform.rotation = glm::normalize(veerQuat * mainTransform.rotation);
}

// Changes direction to veer plane into
void Plane::skewLeft(float deltaTime){
    float veerAmount = deltaTime * veerSpeed;
    glm::quat veerQuat = glm::angleAxis(-veerAmount, glm::vec3(0.0f, 0.0f, 1.0f));
    mainTransform.rotation = glm::normalize(veerQuat * mainTransform.rotation);
}

// Changes direction to veer plane into
void Plane::skewRight(float deltaTime){
    float veerAmount = deltaTime * veerSpeed;
    glm::quat veerQuat = glm::angleAxis(veerAmount, glm::vec3(0.0f, 0.0f, 1.0f));
    mainTransform.rotation = glm::normalize(veerQuat * mainTransform.rotation);
}

// Changes direction to veer plane into
void Plane::veerUp(float deltaTime){
    float veerAmount = deltaTime * veerSpeed;
    glm::quat veerQuat = glm::angleAxis(veerAmount, glm::vec3(1.0f, 0.0f, 0.0f));
    mainTransform.rotation = glm::normalize(veerQuat * mainTransform.rotation);
}

// Changes direction to veer plane into
void Plane::veerDown(float deltaTime){
    float veerAmount = deltaTime * veerSpeed;
    glm::quat veerQuat = glm::angleAxis(-veerAmount, glm::vec3(1.0f, 0.0f, 0.0f));
    mainTransform.rotation = glm::normalize(veerQuat * mainTransform.rotation);
}

// Accelerates the plane forwards
void Plane::accel(float deltaTime){
    velocity -= deltaTime * acceleration * mainTransform.getFoward();
}

// Causes light 
void Plane::fireLights(){
    if(currentLight == nullptr){
        currentLight.reset(
            new SpotLightObject(&spotlightTransform , renderManager, glm::vec3(0.3f),glm::vec3(0.8f),glm::vec3(0.4f), glm::cos(glm::radians(12.5f)), glm::cos(glm::radians(17.5f)), 1.0f, 0.05, 0.032));
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

    velocity -= deltaTime * gravity * glm::vec3(0.0f,1.0f, 0.0f); 
    velocity += deltaTime * lift * (glm::vec3(0.0f,1.0f, 0.0f) * mainTransform.getWorldRotation());
    velocity -= deltaTime * drag * velocity;
}