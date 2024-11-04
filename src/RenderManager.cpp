#include "RenderManager.hpp"
#include "DirLightObject.hpp"
#include "PointLightObject.hpp"
#include "Transform.hpp"
#include "Shader.hpp"
#include "Model.hpp"
#include "Mesh.hpp"
#include "ModelObject.hpp"

#include <iostream>
#include <string>
#include <map>
#include <vector>


void RenderManager::insertModel(char* path, char* base){
    Model* gotModel = new Model(path, base);
    std::vector<ModelObject*> initObList;
    modelList.push_back(gotModel);
    models.insert({gotModel, initObList});
}

void RenderManager::draw(){
    givenShader->use();
    for(unsigned int i = 0; i < modelList.size(); i++){
        std::vector<ModelObject*>* modelObList = &models[modelList[i]];
        for(unsigned int t = 0; t < modelObList->size(); t++){
            modelList[i]->Draw(*givenShader, *((*modelObList)[t]->transform));
        }
    }
    glUseProgram(0);
}

void RenderManager::predraw(){
    // Some options
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glViewport(0,0,WIDTH, HEIGHT);
    glClearColor(1.f, 1.f, 0.f, 1.f);
    glClear(GL_DEPTH_BUFFER_BIT| GL_COLOR_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    // Main shader implementation
    givenShader->use();
    // Create transformation matrices
    glm::mat4 viewMatrix = givenCamera->getViewMat();

    // Inserting lights
    for(int i = 0; i < dirLightList.size(); i++){
        dirLightList[i]->render(i, givenShader);
    }
    givenShader->setInt("u_dirLightLength", dirLightList.size());

    for(int i = 0; i < pointLightList.size(); i++){
        pointLightList[i]->render(i, givenShader);
    }
    givenShader->setInt("u_pointLightLength", pointLightList.size());

    // Inserting into uniform variables
    givenShader->setMatrix("u_perspectiveMat", perspectiveMat);
    givenShader->setMatrix("u_viewMat", viewMatrix);
    givenShader->setVec3("u_viewPos", givenCamera->getEyeLoc());
    givenShader->setInt("u_givenTextures", 0);
}

void RenderManager::Quit(){
    for(unsigned int i = 0; i < modelList.size(); i++){
        std::vector<ModelObject*>* modelObList = &models[modelList[i]];
        for(unsigned int t = 0; t < modelObList->size(); t++){
            delete (*modelObList)[t];
        }
        modelObList->clear();
        delete modelList[i];
    }
    for(unsigned int i = 0; i < dirLightList.size(); i++){
        delete dirLightList[i];
    }
    for(unsigned int i = 0; i < pointLightList.size(); i++){
        delete pointLightList[i];
    }
    pointLightList.clear();
    dirLightList.clear();
    modelList.clear();
    models.clear();
    removeMap.clear();
    delete this;
}

RenderManager::RenderManager(Camera* setCamera, glm::mat4 setMat, Shader* setShader, int setHeight, int setWidth){
    HEIGHT = setHeight;
    WIDTH = setWidth;
    givenCamera = setCamera;
    perspectiveMat = setMat;
    givenShader = setShader;
}

void RenderManager::insertModelOb(ModelObject* modelOb, int modelIndex){
    Model* gotModel = modelList[modelIndex];
    models[gotModel].push_back(modelOb);
    removeMap.insert({modelOb, gotModel});
}

void RenderManager::detactchModelObject(ModelObject* attachedObject){
    if (removeMap.find(attachedObject) == removeMap.end()) {
        std::cout << "ERROR::MODEL OBJECT NOT FOUND IN REMOVE MAP" << std::endl;
        return;
    }
    
    Model* gotModel = removeMap[attachedObject];
    removeMap.erase(attachedObject);
    auto find = std::find(models[gotModel].begin(), models[gotModel].end(), (attachedObject));
    if(find != models[gotModel].end()){
        models[gotModel].erase(find);
    }
    else{
        std::cout << "ERROR::MODEL OBJECT NOT FOUND WITHIN RENDER MANAGEMENT" << std::endl;
    }
    delete this;
}

void RenderManager::insertDirLightOb(DirLightObject* lightOb){
    dirLightList.push_back(lightOb);
}

void RenderManager::detatchDirLightOb(DirLightObject* lightOb){
    auto find = std::find(dirLightList.begin(), dirLightList.end(), (lightOb));
    if(find != dirLightList.end()){
        dirLightList.erase(find);
    }
}

void RenderManager::insertPointLightOb(PointLightObject* lightOb){
    pointLightList.push_back(lightOb);
}

void RenderManager::detatchPointLightOb(PointLightObject* lightOb){
    auto find = std::find(pointLightList.begin(), pointLightList.end(), (lightOb));
    if(find != pointLightList.end()){
        pointLightList.erase(find);
    }
}