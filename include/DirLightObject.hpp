#ifndef DIRLIGHTOBJECT_HPP
#define DIRLIGHTOBJECT_HPP

#include "LightObject.hpp"
#include "Shader.hpp"
#include "Transform.hpp"

// Represents a directional light
// The foward vector of the quaternion is what is used to find the vector of direction.
class DirLightObject : public LightObject{
    public:
        DirLightObject(Transform* setTransformObject, RenderManager* setManager, glm::vec3 setAmbient, glm::vec3 setDiffuse, glm::vec3 setSpectral);

        // Plugs light parameters into uniforms
        void render(int index, Shader* givenShader) override;

        // Releases light object from the render manager
        ~DirLightObject();
}; 

#endif