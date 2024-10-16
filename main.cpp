#include <SDL2/SDL.h>
#include <SDL2/SDL_surface.h>
#include <glad/glad.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <filesystem>

#include "Model.hpp"
#include "Vertex.hpp"
#include "Mesh.hpp"
#include "Camera.hpp"
#include "stb_image.h"
#include "Shader.hpp"
#include "Texture.hpp"
#include "TextureArray.hpp"

#define GLCheck(x) GLClearErrors(); x; GLCheckErrorStatus(#x, __LINE__ );
// Current compile command
//g++ main.cpp ./src/* -I./include/ -I./include/glm-master -std=c++11 -o a.out -lSDL2 -ldl

// Globals
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

SDL_Window* graphicsWindow = nullptr;
SDL_GLContext openGLContext = nullptr;
bool gQuit = false;

// Textures
TextureArray* Textures;
Model* guitarModel;

/// Vertice specifiers (VAOs, VBOs, IBOs)
GLuint IBO = 0;
GLuint lightVAO = 0;
GLuint lightVBO = 0;

// Shaders
const char* vertexShaderFileName = "../../shaders/vertex.glsl";
const char* fragmentShaderFileName = "../../shaders/frag.glsl";
const char* lightFragmentShaderFileName = "../../shaders/lightFrag.glsl";

// Model
char* base = "/Users/jianwending/Documents/ProjectsFolder/Current Projects/OpenGL_jam/models/backpack/backpack.obj";
char* backpackPath = "../../models/backpack/";

Shader* GraphicsPipeline;
Shader* LightGraphicsPipeline;
Mesh* boxMesh;

// Transform variables
GLfloat u_offSet = -5;
GLfloat u_rotate = 0;
GLfloat u_scale = 0.5;

// Lighting variables
GLfloat ambienceVal = 1.0f;
glm::vec3 lightPos = glm::vec3(1.0f,1.0f,1.0f);

Camera viewCam;

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

std::string getFileString(const std::string& fileName){
    try{
        std::string result = "";
        std::string line = "";
        std::ifstream myFile(fileName.c_str());
        if(myFile.is_open()){
            while(std::getline(myFile, line)){
                result += line + "\n";
            }
            myFile.close();
        }
        return result;
    }
    catch(std::exception& e){
        std::cout << "File -" + fileName + "- unable to be opened" << std::endl;
        exit(1);
    }
}

void getOpenGLVersionInfo(){
    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl; 
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl; 
    std::cout << "Version: " << glGetString(GL_VERSION) << std::endl; 
    std::cout << "Shaidng Language: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl; 

}
void getInput(){
    SDL_Event e;
    while(SDL_PollEvent(&e) != 0){
        if(e.type == SDL_QUIT){
            std::cout << "Terminating" << std::endl;
            gQuit = true;
        }
        else if(e.type == SDL_MOUSEMOTION){
            viewCam.mouseLook(e.motion.xrel,e.motion.yrel);
        }
    }
    u_rotate -= 0.0001f;
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if(state[SDL_SCANCODE_UP]||state[SDL_SCANCODE_W]){
        viewCam.moveFoward(0.001f);
    }
    if(state[SDL_SCANCODE_DOWN]||state[SDL_SCANCODE_S]){
        viewCam.moveBackwards(0.001f);
    }
    if(state[SDL_SCANCODE_LEFT]||state[SDL_SCANCODE_A]){
        viewCam.moveLeft(0.001f);
    }
    if(state[SDL_SCANCODE_RIGHT]||state[SDL_SCANCODE_D]){
        viewCam.moveRight(0.001f);
    }
    if(state[SDL_SCANCODE_LSHIFT]){
        viewCam.moveDown(0.001f);
    }
    if(state[SDL_SCANCODE_SPACE]){
        viewCam.moveUp(0.001f);
    }
}

void insertUniform1f(GLfloat insert, const char* name, GLuint shaderProgram){
    GLint location = glGetUniformLocation(shaderProgram, name);
    if(location >= 0){
        glUniform1f(location, insert);
    }
    else{
        std::cout << "error in -" << name << "- possibly an error in spelling" << std::endl;
        exit(EXIT_FAILURE);
    }
}
void insertUniform1i(GLint textureLoc, const char* name, GLuint shaderProgram){
    GLint location = glGetUniformLocation(shaderProgram, name);
    if(location >= 0){
        glUniform1i(location, textureLoc);
    }
    else{
        std::cout << "error in -" << name << "- possibly an error in spelling" << std::endl;
        exit(EXIT_FAILURE);
    }
}
void insertUniform3f(glm::vec3 insert, const char* name, GLuint shaderProgram){
    GLint location = glGetUniformLocation(shaderProgram, name);
    if(location >= 0){
        glUniform3f(location, insert.x, insert.y, insert.z);
    }
    else{
        std::cout << "error in -" << name << "- possibly an error in spelling" << std::endl;
        exit(EXIT_FAILURE);
    }
}
void insertUniformMatrix4fv(glm::mat4x4 insert, const char* name, GLuint shaderProgram){
    GLint location = glGetUniformLocation(shaderProgram, name);
    if(location >= 0){
        glUniformMatrix4fv(location, 1, GL_FALSE, &insert[0][0]);
    }
    else{
        std::cout << "error in -" << name << "- possibly an error in spelling" << std::endl;
        exit(EXIT_FAILURE);
    }
}
void preDrawFunc(){
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glViewport(0,0,WINDOW_WIDTH, WINDOW_HEIGHT);
    glClearColor(1.f, 1.f, 0.f, 1.f);
    glClear(GL_DEPTH_BUFFER_BIT| GL_COLOR_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    // Main shader implementation
    GraphicsPipeline->use();
    // Create transformation matrices
    glm::mat4 viewMatrix = viewCam.getViewMat();
    glm::mat4 perspectiveMatrix = glm::perspective(glm::radians(45.0f), (float)WINDOW_WIDTH/(float)WINDOW_HEIGHT, 0.1f, 10.0f);
    glm::mat4 modelMatrix = glm::mat4x4(1.0f);
    glm::quat testQuat = glm::normalize(glm::quat(1.0f,0.0f,0.0f,0.0f));
    glm::quat test2Quat = glm::normalize(glm::quat(cos(u_rotate),0.0f,sin(u_rotate),0.0f));
    glm::quat test3Quat = testQuat * test2Quat;
    glm::mat4 rotationMatrix = glm::mat4_cast(test3Quat);
    glm::mat4 lightModelMatrix = glm::translate(modelMatrix, glm::vec3(u_offSet/5,-u_offSet/5,u_offSet));
    modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f,0.0f,u_offSet));
    modelMatrix = modelMatrix * rotationMatrix;
    lightModelMatrix = lightModelMatrix * rotationMatrix;
    modelMatrix = glm::scale(modelMatrix, glm::vec3(u_scale,u_scale,u_scale));
    lightModelMatrix = glm::scale(lightModelMatrix, glm::vec3(u_scale/3,u_scale/3,u_scale/3));
    // Inserting into uniform variables
    GraphicsPipeline->setMatrix("u_perspectiveMat", perspectiveMatrix);
    GraphicsPipeline->setMatrix("u_modelMat",modelMatrix);
    GraphicsPipeline->setMatrix("u_viewMat", viewMatrix);
    GraphicsPipeline->setVec3("u_lightColor", glm::vec3(1.0f));
    GraphicsPipeline->setInt("u_givenTextures", 0);
    GraphicsPipeline->setFloat("u_ambienceStrength", ambienceVal);
    // Light shader implementations
    LightGraphicsPipeline->use();
    LightGraphicsPipeline->setMatrix("u_perspectiveMat", perspectiveMatrix);
    LightGraphicsPipeline->setMatrix("u_modelMat", lightModelMatrix);
    LightGraphicsPipeline->setMatrix("u_viewMat",viewMatrix);
}

void drawFunc(){
    GLCheck(guitarModel->Draw(*GraphicsPipeline);)

    LightGraphicsPipeline->use();
    glBindVertexArray(lightVAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    
    glUseProgram(0);
}

void InitializeProgram(){
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cout << "SDL2 could not initialize video system" 
            << std::endl;
        exit(1);
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,24);

    graphicsWindow = SDL_CreateWindow("BirdbrainProgram", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
    if(graphicsWindow == nullptr){
        std::cout << "SDL_Window could not be created" 
            << std::endl;
        exit(1);
    }
    openGLContext = SDL_GL_CreateContext(graphicsWindow);
    if(openGLContext == nullptr){
        std::cout << "Context not avaliable" 
            << std::endl;
        exit(1);
    }
    //Initialize Glad Libary
    if(!gladLoadGLLoader(SDL_GL_GetProcAddress)){
        std::cout << "Glad unable to be initialized" 
            << std::endl;
        exit(1);
    }
    getOpenGLVersionInfo();
}

GLuint CompileShader(GLuint type, const std::string& source){
    GLuint shaderObject;

    if(type == GL_VERTEX_SHADER){
        shaderObject = glCreateShader(GL_VERTEX_SHADER);

    }else if(type == GL_FRAGMENT_SHADER){
        shaderObject = glCreateShader(GL_FRAGMENT_SHADER);
    }

    const char* src = source.c_str();
    glShaderSource(shaderObject, 1, &src, nullptr);
    glCompileShader(shaderObject);

    int success;
    char infoLog[512];
    glGetShaderiv(shaderObject, GL_COMPILE_STATUS,  &success);
    if(!success){
        glGetShaderInfoLog(shaderObject, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
        if(type == GL_VERTEX_SHADER){
            std::cout << "ERROR OCCURED IN VERTEX SHADER"<< std::endl;
        }else if(type == GL_FRAGMENT_SHADER){
            std::cout << "ERROR OCCURED IN FRAGMENT SHADER"<< std::endl;
        }
        glDeleteShader(shaderObject);
        return 0;
    }
    return shaderObject;
}

GLuint CreateShaderProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource){
    GLuint programObject = glCreateProgram();
    GLuint vertexShader = CompileShader(GL_VERTEX_SHADER, vertexShaderSource);
    GLuint fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
    glAttachShader(programObject, vertexShader);
    glAttachShader(programObject, fragmentShader);
    glLinkProgram(programObject);

    glValidateProgram(programObject);

    glDetachShader(programObject, vertexShader);
    glDetachShader(programObject, fragmentShader);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return programObject;
}
void CreateGraphicsPipeline(){
    GraphicsPipeline = new Shader(vertexShaderFileName, fragmentShaderFileName);
    LightGraphicsPipeline = new Shader(vertexShaderFileName, lightFragmentShaderFileName);
}

void VertexSpecification(){

    std::vector<float> verticeData{
        // Vertex 0
        -0.5f, -0.5f, -0.5f, // Vector
        1.0f, 0.0f, 0.0f,   // Color
        0.0f,0.0f,         // Texture map
        // Vertex 1
        0.5f, -0.5f, -0.5f, // Vector
        0.0f, 1.0f, 0.0f,  // Color
        1.0f,0.0f,        // Texture map
        // Vertex 2
        -0.5f, 0.5f, -0.5f, // Vector
        0.0f, 0.0f, 1.0f,  //Color
        0.0f,1.0f,        // Texture map
        // Vertex 3
        0.5f, 0.5f, -0.5f, // Vector
        0.0f, 0.0f, 1.0f, // Color
        1.0f,1.0f,        // Texture map
        // Vertex 4
        -0.5f, -0.5f, 0.5f, // Vector
        1.0f, 0.0f, 0.0f,  // Color
        1.0f,0.0f,        // Texture map
        // Vertex 5
        0.5f, -0.5f, 0.5f, // Vector
        0.0f, 1.0f, 0.0f, // Color
        2.0f,0.0f,       // Texture map
        // Vertex 6
        -0.5f, 0.5f, 0.5f, // Vector
        0.0f, 0.0f, 1.0f, //Color
        1.0f,1.0f,       // Texture map
        // Vertex 7
        0.5f, 0.5f, 0.5f, // Vector
        0.0f, 0.0f, 1.0f,// Color
        2.0f,1.0f,      // Texture map
    };

    std::vector<Vertex> vertexData{
        // Vertex 0
        *(new Vertex(*(new glm::vec3(-0.5f, -0.5f, -0.5f)) , *(new glm::vec3(0.0f,0.0f,0.0f)), *(new glm::vec2(0.0f,0.0f)))), 
        // Vertex 1
        *(new Vertex(*(new glm::vec3(0.5f, -0.5f, -0.5f)), *(new glm::vec3(0.0f,0.0f,0.0f)), *(new glm::vec2(1.0f,0.0f)))),
        // Vertex 2
        *(new Vertex(*(new glm::vec3(-0.5f, 0.5f, -0.5f)), *(new glm::vec3(0.0f,0.0f,0.0f)), *(new glm::vec2(0.0f,1.0f)))),
        // Vertex 3
        *(new Vertex(*(new glm::vec3(0.5f, 0.5f, -0.5f)), *(new glm::vec3(0.0f,0.0f,0.0f)), *(new glm::vec2(1.0f,1.0f)))),
        // Vertex 4
        *(new Vertex(*(new glm::vec3(-0.5f, -0.5f, 0.5f)), *(new glm::vec3(0.0f,0.0f,0.0f)), *(new glm::vec2(1.0f,0.0f)))),
        // Vertex 5
        *(new Vertex(*(new glm::vec3(0.5f, -0.5f, 0.5f)), *(new glm::vec3(0.0f,0.0f,0.0f)), *(new glm::vec2(2.0f,0.0f)))),
        // Vertex 6
        *(new Vertex(*(new glm::vec3(-0.5f, 0.5f, 0.5f)), *(new glm::vec3(0.0f,0.0f,0.0f)), *(new glm::vec2(1.0f,1.0f)))),
        // Vertex 7
        *(new Vertex(*(new glm::vec3(0.5f, 0.5f, 0.5f)), *(new glm::vec3(0.0f,0.0f,0.0f)), *(new glm::vec2(2.0f,1.0f))))
    };

    std::vector<GLfloat> lightVerticeData{
        // Vertex 0
        -0.5f, -0.5f, -0.5f, // Vector
        // Vertex 1
        0.5f, -0.5f, -0.5f, // Vector
        // Vertex 2
        -0.5f, 0.5f, -0.5f, // Vector
        // Vertex 3
        0.5f, 0.5f, -0.5f, // Vector
        // Vertex 4
        -0.5f, -0.5f, 0.5f, // Vector
        // Vertex 5
        0.5f, -0.5f, 0.5f, // Vector
        // Vertex 6
        -0.5f, 0.5f, 0.5f, // Vector
        // Vertex 7
        0.5f, 0.5f, 0.5f, // Vector
    };
    std::vector<GLuint> indexBufferData{2,0,1, 3,2,1, 5,4,6, 5,6,7, 4,0,2, 6,4,2, 5,1,3, 7,5,3, 6,2,3, 7,6,3, 4,0,1, 5,4,1};

    // Generates Texture
    std::vector<Texture> textureList;
    Texture* tex1Data;
    tex1Data = new Texture("../../textures/testTexture.jpeg");
    textureList.push_back(*tex1Data);
    Texture* tex2Data;
    tex2Data = new Texture("../../textures/awesomeface.png");
    textureList.push_back(*tex2Data);
    GLCheck(Textures = new TextureArray(textureList);)
    tex1Data->free();
    tex2Data->free();
    
    // Compiles into mesh
    GLCheck(guitarModel = new Model(base,backpackPath);)

    // Generates light VAO
    // Generates VAO
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);

    // Generates VBO
    glGenBuffers(1, &lightVBO);
    glBindBuffer(GL_ARRAY_BUFFER, lightVBO);
    glBufferData(GL_ARRAY_BUFFER, lightVerticeData.size() * sizeof(GLfloat), lightVerticeData.data(), GL_STATIC_DRAW);

    //Binds IBO
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBufferData.size()*sizeof(GLuint), indexBufferData.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glBindVertexArray(0);
    glDisableVertexAttribArray(0);
}

void MainLoop(){
    while (!gQuit){
        getInput();

        preDrawFunc();

        drawFunc();

        SDL_GL_SwapWindow(graphicsWindow);
    }
}

void CleanUp(){
    //Destroy window
    SDL_DestroyWindow(graphicsWindow);
    //Quit SDL subsystems
    SDL_Quit();
}

// Test
int main(){
    // Initializes SDL and OpenGL while opening window
    InitializeProgram();

    // Specifies VAO and VBO
    VertexSpecification();

    // Creates shaders, both fragment and vector
    CreateGraphicsPipeline();

    // Continually draws over file
    MainLoop();

    // Ends running subsystems
    CleanUp();

    return 0;
}
