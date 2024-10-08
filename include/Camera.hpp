#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

class Camera{
    private:
        glm::vec3 eye;
        glm::quat viewOrientation;
        glm::vec3 upVector;
        glm::vec2 oldMousePosition;
    public:
        Camera();

        glm::mat4 getViewMat() const;
        glm::vec3 getViewLocation() const;
        glm::vec3 getFowardVec();
        void mouseLook(float mouseX, float mouseY);
        void moveFoward(float speed);
        void moveBackwards(float speed);
        void moveLeft(float speed);
        void moveRight(float speed);
        void moveUp(float speed);
        void moveDown(float speed);
    
};
#endif
