    #ifndef LIGHTOBJECT_HPP
    #define LIGHTOBJECT_HPP

    #include "Transform.hpp"
    #include "RenderManager.hpp"
    #include "Shader.hpp"
    #include "Mesh.hpp"
    #include "string"

    #include <glm/glm.hpp>

    // Represents a single light of any kind to be represented in the render manager
    class LightObject{
        public:  

            LightObject(Transform* setTransform, RenderManager* setManager, glm::vec3 setAmbient, glm::vec3 setDiffuse, glm::vec3 setSpectral);
            
            // Plugs light parameters into uniforms
            virtual void render(int index, Shader* givenShader) = 0;

            Transform* givenTransform;
            glm::vec3 ambient;
            glm::vec3 diffuse;
            glm::vec3 spectral;

        protected:
            RenderManager* givenManager;
    };


    #endif