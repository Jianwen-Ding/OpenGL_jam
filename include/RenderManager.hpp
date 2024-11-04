#ifndef RENDERMANAGER_HPP
#define RENDERMANAGER_HPP

#include "ModelObject.hpp"
#include "LightObject.hpp"
#include "Camera.hpp"
#include "Transform.hpp"
#include "Shader.hpp"
#include "Model.hpp"
#include "Mesh.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glad/glad.h>
#include <string>
#include <map>
#include <vector>

class DirLightObject;
class PointLightObject;

class RenderManager{
    public:

        // Initializes model and adds to manager
        void insertModel(char* path, char* base);

        // Draws the models and objects inserted inside
        void draw();
        // Prepares to draw all of the afformentioned things
        void predraw();

        // Actually initializes state
        RenderManager(Camera* setCamera, glm::mat4 setMat, Shader* givenShader, int setWidth, int setHeight);

        // Inserts the lights
        void insertDirLightOb(DirLightObject* lightOb);
        void insertPointLightOb(PointLightObject* lightOb);

        // Removes and deletes the light objects from the render data
        void detatchDirLightOb(DirLightObject* lightOb);
        void detatchPointLightOb(PointLightObject* lightOb);

        // Inserts the model object for the rendered data
        void insertModelOb(ModelObject* modelOb, int modelIndex);
        // Removes and deletes the model object from rendered data
        void detactchModelObject(ModelObject* attachedObject);

        void Quit();

    private:

        // Model/Model Object navigation
        std::vector<Model*> modelList;
        std::map<Model*, std::vector<ModelObject*>> models;
        std::map<ModelObject*, Model*> removeMap;

        // Light Object navigation
        std::vector<DirLightObject*> dirLightList;
        std::vector<PointLightObject*> pointLightList;

        // Rendering pipeline object/fields
        Camera* givenCamera;
        glm::mat4 perspectiveMat;
        Shader* givenShader;

        // Width/height
        int WIDTH;
        int HEIGHT;
};

#endif