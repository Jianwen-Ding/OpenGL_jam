#ifndef RENDERMANAGER_HPP
#define RENDERMANAGER_HPP

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

class RenderManager{
    public:
        // A class representing the information needed to load a single instance 
        // Maybe I would want to expand on this later but for now it will only house transform
        class ModelObject{
            public:
                Transform* transform;
                // Detaches from render manager
                ModelObject(Transform* transformObject, int modelIndex, RenderManager* setManager);
                void Destroy();
            private:
                RenderManager* manager;
                int model;
                int obIdx;
        };


        // Initializes model and adds to manager
        void insertModel(char* path, char* base);

        // Draws the models and objects inserted inside
        void draw();
        // Prepares to draw all of the afformentioned things
        void predraw();

        // Actually initializes state
        RenderManager(Camera* setCamera, glm::mat4 setMat, Shader* givenShader, int setWidth, int setHeight);

        void Quit();

    private:
        // Inserts the model object for the rendered data
        void insertModelOb(ModelObject* modelOb, int modelIndex);
        // Removes and deletes the model object from rendered data
        void detactchModelObject(ModelObject* attachedObject);

        // Model/Model Object navigation
        std::vector<Model*> modelList;
        std::map<Model*, std::vector<ModelObject*>> models;
        std::map<ModelObject*, Model*> removeMap;

        // Rendering pipeline object/fields
        Camera* givenCamera;
        glm::mat4 perspectiveMat;
        Shader* givenShader;

        // Width/height
        int WIDTH;
        int HEIGHT;
};

#endif