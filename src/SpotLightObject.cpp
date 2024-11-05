#include "SpotLightObject.hpp"

SpotLightObject::SpotLightObject(
            Transform* setTransformObject, 
            RenderManager* setManager, 
            glm::vec3 setAmbient, 
            glm::vec3 setDiffuse, 
            glm::vec3 setSpectral,
            float setCutOff,
            float setOutCutOff,
            float setLinear, 
            float setQuadratic, 
            float setConstant) : 
LightObject(setTransformObject, setManager, setAmbient, setDiffuse, setSpectral),
cutOff(setCutOff),
outCutOff(setOutCutOff),
linear(setLinear),
quadratic(setQuadratic),
constant(setConstant) {
    givenManager->insertSpotLightOb(this);
}

void SpotLightObject::render(int index, Shader* givenShader) {
    std::string base = "u_spotLight[" + std::to_string(index) + "]";
    givenShader->setVec3(base + ".position", givenTransform->position);
    givenShader->setVec3(base + ".direction", givenTransform->getFoward());
    givenShader->setVec3(base + ".ambient", ambient);
    givenShader->setVec3(base + ".diffuse", diffuse);
    givenShader->setVec3(base + ".spectral", spectral);
    givenShader->setFloat(base + ".constant", constant);
    givenShader->setFloat(base + ".linear", linear);
    givenShader->setFloat(base + ".quadratic", quadratic);
    givenShader->setFloat(base + ".cutOff", cutOff);
    givenShader->setFloat(base + ".outerCutOff", outCutOff);
}

void SpotLightObject::Destroy() {
    givenManager->detatchSpotLightOb(this);
}