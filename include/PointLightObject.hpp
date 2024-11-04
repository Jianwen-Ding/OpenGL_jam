#ifndef POINTLIGHTOBJECT_HPP
#define POINTLIGHTOBJECT_HPP

#include "LightObject.hpp"

// Represents a point light, a light that 
// at a certain points that becomes less bright the further away it is
class PointLightObject : public LightObject{
    public:
        PointLightObject(
            Transform* setTransformObject, 
            RenderManager* setManager, 
            glm::vec3 setAmbient, 
            glm::vec3 setDiffuse, 
            glm::vec3 setSpectral, 
            float setLinear, 
            float setQuadratic, 
            float setConstant);

        void render(int index, Shader* givenShader) override;
        void Destroy() override;

    private:

        // Attenuation (light falloff) vars
        float linear;
        float quadratic;
        float constant;
};

#endif