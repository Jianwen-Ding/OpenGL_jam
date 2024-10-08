#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include <glm/glm.hpp>
#include <fstream>
#include <sstream>
#include <glad/glad.h>

class Shader{
    public:
        // Program ID
        GLuint ID;

        // constructor reads and builds the shader
        Shader(const char* vertexPath, const char* fragmentPath);
        // uses/activates the shader
        void use();
        // utility uniform functions
        void setBool(const std::string &name, bool value) const;
        void setInt(const std::string &name, int value) const;
        void setFloat(const std::string &name, float value) const;
        void setVec3(const std::string &name, glm::vec3 value) const;
        void setMatrix(const std::string &name, glm::mat4 value) const;
};
#endif