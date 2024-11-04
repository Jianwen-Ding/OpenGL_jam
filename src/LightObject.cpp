#include "LightObject.hpp"

LightObject::LightObject(Transform* setTransform, RenderManager* setManager, glm::vec3 setAmbient, glm::vec3 setDiffuse, glm::vec3 setSpectral)
:   givenTransform(setTransform),
    givenManager(setManager),
    ambient(setAmbient),
    diffuse(setDiffuse),
    spectral(setSpectral) {
}

LightObject::~LightObject(){
    this->Destroy();
}