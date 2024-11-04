#include "PointLightObject.hpp"

PointLightObject::PointLightObject(
            Transform* setTransformObject, 
            RenderManager* setManager, 
            glm::vec3 setAmbient, 
            glm::vec3 setDiffuse, 
            glm::vec3 setSpectral, 
            float setLinear, 
            float setQuadratic, 
            float setConstant) : 
LightObject(setTransformObject, setManager, setAmbient, setDiffuse, setSpectral),
linear(setLinear),
quadratic(setQuadratic),
constant(setConstant) {
    setManager->insertPointLightOb(this);
}

void PointLightObject::render(int index, Shader* givenShader) {
    std::string base = "u_pointLight[" + std::to_string(index) + "]";
    givenShader->setVec3(base + ".position", givenTransform->position);
    givenShader->setVec3(base + ".ambient", ambient);
    givenShader->setVec3(base + ".diffuse", diffuse);
    givenShader->setVec3(base + ".spectral", spectral);
    givenShader->setFloat(base + ".constant", constant);
    givenShader->setFloat(base + ".linear", linear);
    givenShader->setFloat(base + ".quadratic", quadratic);
}

void PointLightObject::Destroy() {
    givenManager->detatchPointLightOb(this);
}