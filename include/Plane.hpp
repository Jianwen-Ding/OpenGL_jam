#ifndef PLANE_HPP
#define PLANE_HPP

#include "Transform.hpp"
#include "Camera.hpp"
#include "ModelObject.hpp"
#include "SpotLightObject.hpp"

#include <glm/glm.hpp>


// Handles the plane flying around in the map
class Plane{
    private:
        // Parameters
        float drag;
        float veerSpeed;
        float gravity;
        float acceleration;
        float lift;
        float maxVel;

        // State Variable
        glm::vec3 velocity;
        Transform mainTransform;
        std::unique_ptr<SpotLightObject> currentLight;

        // Cached Variables
        Camera* givenCamera;
        RenderManager* renderManager;
        std::unique_ptr<ModelObject> currentModel;
        Transform spotlightTransform;
        Transform cameraTransform;
    public:
        Plane(Camera* setCamera, RenderManager* manager, int planeModelIdx, float setVeer, float setDrag, float setGravity, float setAccel, float setLift, float setMaxVel, glm::vec3 initPos);

        void veerMouse(float deltaTime, float MouseX, float MouseY);
        // Changes direction to veer plane into
        void veerLeft(float deltaTime);

        // Changes direction to veer plane into
        void veerRight(float deltaTime);

        // Changes direction to veer plane into
        void skewLeft(float deltaTime);

        // Changes direction to veer plane into
        void skewRight(float deltaTime);

        // Changes direction to veer plane into
        void veerUp(float deltaTime);

        // Changes direction to veer plane into
        void veerDown(float deltaTime);

        // Accelerates the plane forwards
        void accel(float deltaTime);

        // Causes lights to go off
        void fireLights();

        // Deactivates lights
        void deactivateLights();

        // Updates the planes physics
        void update(float deltaTime);
        
};

#endif