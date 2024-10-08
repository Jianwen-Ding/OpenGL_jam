#include "Camera.hpp"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(){
    eye = glm::vec3(0.0f,0.0f,0.0f);
    viewOrientation = glm::quat(1.0f,0.0f,0.0f,0.0f);
    upVector = glm::vec3(0.0f,1.0f,0.0f);
}

void Camera::mouseLook(float mouseX, float mouseY){
    static bool firstLook = true;
    glm::vec2 currentMouse = glm::vec2(mouseX,mouseY);
    glm::quat yRot = glm::normalize(glm::quat(cos(-currentMouse.y/200),sin(-currentMouse.y/200),0,0));
    glm::quat xRot = glm::normalize(glm::quat(cos(-currentMouse.x/200),0,sin(-currentMouse.x/200),0));
    viewOrientation = viewOrientation * xRot * yRot;
}

glm::vec3 Camera::getViewLocation() const{
    return viewOrientation * (glm::vec3(0,0,-1.0f));
}

glm::mat4 Camera::getViewMat() const{
    return glm::lookAt(eye, getViewLocation() + eye, upVector);
}
glm::vec3 Camera::getFowardVec(){
    glm::vec3 viewLoc = getViewLocation();
    viewLoc = glm::normalize(glm::vec3(viewLoc.x, 0, viewLoc.z));
    return viewLoc;
}

void Camera::moveFoward(float speed){
    eye += getFowardVec() * speed;
}
void Camera::moveBackwards(float speed){
    eye -= getFowardVec() * speed;
}
void Camera::moveLeft(float speed){
    eye -= glm::cross(getFowardVec(), glm::vec3(0.0f,1.0f,0.0f)) * speed;
}
void Camera::moveRight(float speed){
    eye += glm::cross(getFowardVec(), glm::vec3(0.0f,1.0f,0.0f)) * speed;
}
void Camera::moveUp(float speed){
    eye.y += speed;
}
void Camera::moveDown(float speed){
    eye.y -= speed;
}