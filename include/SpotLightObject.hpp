#ifndef SPOTLIGHTOBJECT_HPP
#define SPOTLIGHTOBJECT_HPP

#include "LightObject.hpp"
#include "Shader.hpp"
#include "Transform.hpp"


// Represents a point light, a light that 
// points to a certain direction from a position that falls off the farther away they are from the center of the beam
class SpotLightObject : public LightObject{
    public:
        SpotLightObject(
            Transform* setTransformObject, 
            RenderManager* setManager, 
            glm::vec3 setAmbient, 
            glm::vec3 setDiffuse, 
            glm::vec3 setSpectral,
            float setCutOff,
            float setOutCutOff,
            float setLinear, 
            float setQuadratic, 
            float setConstant);

        void render(int index, Shader* givenShader) override;
        void Destroy() override;

        // Intensity (light difference from center) var
        float cutOff;
        float outCutOff;

        // Attenuation (light falloff) vars
        float linear;
        float quadratic;
        float constant;
};


#endif