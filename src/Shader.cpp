#include "Shader.hpp"

#include <iostream>
#include <string>
#include <glm/glm.hpp>
#include <fstream>
#include <sstream>
#include <glad/glad.h>

// Constructor of shader
Shader::Shader(const char* vertexPath, const char* fragmentPath){
    // >>> Gets code from files in text form <<<
    // Code extractes from file
    std::string vertexCode;
    std::string fragmentCode;
    // File readers
    std::ifstream vertexFile;
    std::ifstream fragmentFile;
    // Causes files to throw on logical/read and writing errors while reading file
    vertexFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fragmentFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try{
        // open files with readers
        vertexFile.open(vertexPath);
        fragmentFile.open(fragmentPath);
        // reads file's buffer into stream
        std::stringstream vertexStream;
        vertexStream << vertexFile.rdbuf();
        std::stringstream fragmentStream;
        fragmentStream << fragmentFile.rdbuf();
        // close file handelers
        vertexFile.close();
        fragmentFile.close();
        // convert stream into string
        vertexCode = vertexStream.str();
        fragmentCode = fragmentStream.str();
    }catch(std::ifstream::failure e){
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    const char* vertexShaderCode = vertexCode.c_str();
    const char* fragmentShaderCode = fragmentCode.c_str();

    // >>> Compiles Shaders <<<
    GLuint vertexShader;
    GLuint fragmentShader;
    int success;
    char infoLog[512];

    // Compiles vertex shader
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
    glCompileShader(vertexShader);
    // Prints any compile errors
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Compiles vertex shader
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderCode, NULL);
    glCompileShader(fragmentShader);
    // Prints any compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Creates the overall shader pipeline
    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);
    // Prints any linking errors
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

// uses/activates the shader
void Shader::use(){
    glUseProgram(ID);
}

// utility uniform functions
void Shader::setBool(const std::string &name, bool value) const{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, int value) const{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setVec3(const std::string &name, glm::vec3 value) const{
    glUniform3f(glGetUniformLocation(ID, name.c_str()), value[0], value[1], value[2]);
}

void Shader::setMatrix(const std::string &name, glm::mat4 value) const{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &value[0][0]);
}