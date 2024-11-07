#include "RenderManager.hpp"
#include "DirLightObject.hpp"
#include "SpotLightObject.hpp"
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

#define GLCheck(x) GLClearErrors(); x; GLCheckErrorStatus(#x, __LINE__ );

static void GLClearErrors(){
    while(glGetError() != GL_NO_ERROR){
    }
}

static bool GLCheckErrorStatus(const char* function, int line){
    GLenum error;
    while ((error = glGetError()) != GL_NO_ERROR) {
        std::cout << "OpenGL error in " << function << " at line " << line << ": ";
        switch (error) {
            case GL_INVALID_ENUM:
                std::cout << "GL_INVALID_ENUM\n";
                break;
            case GL_INVALID_VALUE:
                std::cout << "GL_INVALID_VALUE\n";
                break;
            case GL_INVALID_OPERATION:
                std::cout << "GL_INVALID_OPERATION\n";
                break;
            case GL_OUT_OF_MEMORY:
                std::cout << "GL_OUT_OF_MEMORY\n";
                break;
            default:
                std::cout << "Unknown error\n";
                break;
        }
        return true;
    }
    return false;
}

void RenderManager::insertModel(const char* path, const char* base){
    Model* gotModel = new Model(path, base);
    std::vector<ModelObject*> initObList;
    modelList.push_back(gotModel);
    models.insert({gotModel, initObList});
}

void RenderManager::draw(){
    
    // Draws skybox
    if(hasSkybox){
        glDepthMask(GL_FALSE);

        skyboxShader->use();
        glBindVertexArray(SkyboxVAO);
        glBindTexture(GL_TEXTURE_CUBE_MAP, SkyboxTextureID);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glDepthMask(GL_TRUE);
    }

    // Draws rest of scene
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

    // Create transformation matrices
    glm::mat4 viewMatrix = givenCamera->getViewMat();

    // Loads shader for draw
    if(hasSkybox){
        skyboxShader->use();

        // Inserting into uniform variables
        skyboxShader->setMatrix("u_perspectiveMat", perspectiveMat);
        skyboxShader->setMatrix("u_viewMat",glm::mat4(glm::mat3(viewMatrix)));
        skyboxShader->setInt("u_cubemap", 0);
    }

    // Main shader implementation
    givenShader->use();

    // Inserting lights
    for(int i = 0; i < dirLightList.size(); i++){
        dirLightList[i]->render(i, givenShader);
    }
    givenShader->setInt("u_dirLightLength", dirLightList.size());

    for(int i = 0; i < pointLightList.size(); i++){
        pointLightList[i]->render(i, givenShader);
    }
    givenShader->setInt("u_pointLightLength", pointLightList.size());

    for(int i = 0; i < spotLightList.size(); i++){
        spotLightList[i]->render(i,givenShader);
    }
    givenShader->setInt("u_spotLightLength", spotLightList.size());

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
    for(unsigned int i = 0; i < spotLightList.size(); i++){
        delete spotLightList[i];
    }
    spotLightList.clear();
    pointLightList.clear();
    dirLightList.clear();
    modelList.clear();
    models.clear();
    removeMap.clear();

    glDeleteVertexArrays(1, &SkyboxVAO);
    glDeleteBuffers(1, &SkyboxVBO);

    delete this;
}

RenderManager::RenderManager(Camera* setCamera, glm::mat4 setMat, Shader* setShader, int setHeight, int setWidth){
    skyboxShader = nullptr;
    hasSkybox = false;
    SkyboxVAO = 0;
    SkyboxVBO = 0;
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

void RenderManager::insertSpotLightOb(SpotLightObject* lightOb){
    spotLightList.push_back(lightOb);
}

void RenderManager::detatchSpotLightOb(SpotLightObject* lightOb){
    auto find = std::find(spotLightList.begin(), spotLightList.end(), (lightOb));
    if(find != spotLightList.end()){
        spotLightList.erase(find);
    }
}

void RenderManager::setLightMap(const char* frontPath, const char* rightPath, const char* leftPath, const char* backPath, const char* bottomPath, const char* topPath, Shader* givenLightShader){
    // Initializes changes needed in rendermanager 
    hasSkybox = true;
    glGenTextures(1, &SkyboxTextureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, SkyboxTextureID);
    skyboxShader = givenLightShader;

    // Loads textures
    Texture frontTex = Texture(frontPath);
    Texture rightTex = Texture(rightPath);
    Texture leftTex = Texture(leftPath);
    Texture backTex = Texture(backPath);
    Texture bottomTex = Texture(bottomPath);
    Texture topTex = Texture(topPath);

    // Inserts texture data into cubemap
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + 0, 0, GL_RGB, rightTex.tWidth, rightTex.tHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, rightTex.tData);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + 1, 0, GL_RGB, leftTex.tWidth, leftTex.tHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, leftTex.tData);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + 3, 0, GL_RGB, topTex.tWidth, topTex.tHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, topTex.tData);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + 2, 0, GL_RGB, bottomTex.tWidth, bottomTex.tHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, bottomTex.tData);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + 4, 0, GL_RGB, frontTex.tWidth, frontTex.tHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, frontTex.tData);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + 5, 0, GL_RGB, backTex.tWidth, backTex.tHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, backTex.tData);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    // Releases textures
    frontTex.free();
    rightTex.free();
    leftTex.free();
    backTex.free();
    bottomTex.free();
    topTex.free();

    // Sets up the skybox shape
    float skyboxVertices[] = {
    // positions          
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
        1.0f,  1.0f, -1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
        1.0f, -1.0f,  1.0f
    };
    
    glGenVertexArrays(1, &SkyboxVAO);
    glGenBuffers(1, &SkyboxVBO);
    glBindVertexArray(SkyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, SkyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    glBindVertexArray(0);
}