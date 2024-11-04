#include "DirLightObject.hpp"

DirLightObject::DirLightObject(Transform* setTransformObject, RenderManager* setManager, glm::vec3 setAmbient, glm::vec3 setDiffuse, glm::vec3 setSpectral) : 
LightObject(setTransformObject, setManager, setAmbient, setDiffuse, setSpectral) {
    setManager->insertDirLightOb(this);
}

void DirLightObject::render(int index, Shader* givenShader) {
    std::string base = "u_dirLight[" + std::to_string(index) + "]";
    givenShader->setVec3(base + ".direction", givenTransform->getFoward());
    givenShader->setVec3(base + ".ambient", ambient);
    givenShader->setVec3(base + ".diffuse", diffuse);
    givenShader->setVec3(base + ".spectral", spectral);
}

void DirLightObject::Destroy() {
    givenManager->detatchDirLightOb(this);
}