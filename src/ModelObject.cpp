#include "ModelObject.hpp"
#include "RenderManager.hpp"
#include "Transform.hpp"

#include <iostream>
#include <string>
#include <map>
#include <vector>

void ModelObject::Destroy(){
    manager->detactchModelObject(this);
}

ModelObject::~ModelObject(){
    manager->detactchModelObject(this);
}

ModelObject::ModelObject(Transform* transformObject, int modelIndex, RenderManager* setManager){
    transform = transformObject;
    manager = setManager;
    model = modelIndex;
    setManager->insertModelOb(this, modelIndex);
}