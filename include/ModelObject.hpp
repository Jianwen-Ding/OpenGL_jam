#ifndef MODELOBJECT_HPP
#define MODELOBJECT_HPP

#include "Transform.hpp"

class RenderManager;

// A class representing the information needed to load a single instance 
// Maybe I would want to expand on this later but for now it will only house transform
class ModelObject{
    public:
        Transform* transform;
        // Detaches from render manager
        ModelObject(Transform* transformObject, int modelIndex, RenderManager* setManager);
        ~ModelObject();
        void Destroy();
    private:
        RenderManager* manager;
        int model;
        int obIdx;
};

#endif