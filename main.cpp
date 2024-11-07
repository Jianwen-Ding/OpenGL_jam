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

#include "Plane.hpp"
#include "RenderManager.hpp"
#include "ModelObject.hpp"
#include "DirLightObject.hpp"
#include "PointLightObject.hpp"
#include "SpotLightObject.hpp"
#include "LightObject.hpp"
#include "Model.hpp"
#include "Vertex.hpp"
#include "Mesh.hpp"
#include "Transform.hpp"
#include "Camera.hpp"
#include "stb_image.h"
#include "Shader.hpp"
#include "Texture.hpp"
#include "TextureArray.hpp"

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

// Current compile command
//g++ main.cpp ./src/* -I./include/ -I./include/glm-master -std=c++11 -o a.out -lSDL2 -ldl

// finds time
unsigned long lastTime;
float deltaTime;

// finds speed
const float speed = 5;

// Globals
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

SDL_Window* graphicsWindow = nullptr;
SDL_GLContext openGLContext = nullptr;
bool gQuit = false;

// Storage
std::unique_ptr<Plane> givenPlane;

Transform transformStore;
Transform transformStore2;
Transform transformStore3;
Transform transformStore4;
Transform transformStore5;
Transform transformStore6;
Transform transformStore7;
Transform transformStore8;
Transform transformStore9;
RenderManager* renderManage;
ModelObject* modelOb;
ModelObject* modelOb2;
DirLightObject* singleLight;
PointLightObject* littleLight;

// Shaders
const char* vertexShaderFileName = "../../shaders/vertex.glsl";
const char* fragmentShaderFileName = "../../shaders/frag.glsl";
const char* lightFragmentShaderFileName = "../../shaders/lightFrag.glsl";
const char* skyboxVertexShaderFileName = "../../shaders/skyboxVertex.glsl";
const char* skyboxFragmentShaderFileName = "../../shaders/skyboxFrag.glsl";

// Model
const char* base = "/Users/jianwending/Documents/ProjectsFolder/CurrentProjects/OpenGL_jam/models/backpack/backpack.obj";
const char* base2 = "/Users/jianwending/Documents/ProjectsFolder/CurrentProjects/OpenGL_jam/models/mb/mb.obj";
const char* backpackPath = "../../models/backpack/";
const char* buildingPath = "../../models/mb/";
const char* base3 = "/Users/jianwending/Documents/ProjectsFolder/CurrentProjects/OpenGL_jam/models/2Fort/2fort.obj";
const char* basePath = "../../models/2Fort/";
const char* base4 = "/Users/jianwending/Documents/ProjectsFolder/CurrentProjects/OpenGL_jam/models/NewPLaneObj/plane.obj";
const char* planePath = "../../models/NewPLaneObj/";


// Paths
const char* skyBackPath = "../../textures/Box_Back.bmp";
const char* skyBottomPath = "../../textures/Box_Bottom.bmp";
const char* skyFrontPath = "../../textures/Box_Front.bmp";
const char* skyLeftPath = "../../textures/Box_Left.bmp";
const char* skyRightPath = "../../textures/Box_Right.bmp";
const char* skyTopPath = "../../textures/Box_Top.bmp";

Shader* SkyboxPipeline;
Shader* GraphicsPipeline;
Shader* LightGraphicsPipeline;

// Transform variables
GLfloat u_offSet = -5;
GLfloat u_rotate = 0;
GLfloat u_scale = 0.5;
GLfloat u_offSet2 = -5;
GLfloat u_scale2 = 0.5;
GLfloat u_lightRot = 0;
GLfloat u_lightFoward = 0;
GLfloat u_lightOrbit = 0;

// Lighting variables
GLfloat ambienceVal = 0.05f;
glm::vec3 lightPos = glm::vec3(1.0f,1.0f,1.0f);

Camera viewCam;

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
    deltaTime = (float)(SDL_GetTicks() - lastTime) / (float)1000;
    lastTime = SDL_GetTicks();
    SDL_Event e;
    while(SDL_PollEvent(&e) != 0){
        if(e.type == SDL_QUIT){
            std::cout << "Terminating" << std::endl;
            gQuit = true;
        }
        else if(e.type == SDL_MOUSEMOTION){
            // givenPlane->veerMouse(deltaTime, e.motion.xrel,e.motion.yrel);
        }
    }
    u_rotate -= 0.1f * deltaTime;
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if(state[SDL_SCANCODE_UP]||state[SDL_SCANCODE_W]){
        givenPlane->veerDown(deltaTime);
    }
    if(state[SDL_SCANCODE_DOWN]||state[SDL_SCANCODE_S]){
        givenPlane->veerUp(deltaTime);
    }
    if(state[SDL_SCANCODE_Q]){
        givenPlane->skewLeft(deltaTime);
    }
    if(state[SDL_SCANCODE_E]){
        givenPlane->skewRight(deltaTime);
    }
    if(state[SDL_SCANCODE_LEFT]||state[SDL_SCANCODE_A]){
        givenPlane->veerLeft(deltaTime);
    }
    if(state[SDL_SCANCODE_RIGHT]||state[SDL_SCANCODE_D]){
        givenPlane->veerRight(deltaTime);
    }
    if(state[SDL_SCANCODE_Z]){
        u_offSet += deltaTime;
    }
    if(state[SDL_SCANCODE_Y]){
        u_lightRot += 0.2 * deltaTime;
    }
    if(state[SDL_SCANCODE_T]){
        u_lightOrbit += 0.01;
        u_lightFoward += 0.01;
    }
    if(state[SDL_SCANCODE_U]){
        u_lightOrbit -= 0.01;
        u_lightFoward -= 0.01;
    }
    if(state[SDL_SCANCODE_LSHIFT]){
        givenPlane->fireLights();
    }
    if(state[SDL_SCANCODE_RSHIFT]){
        givenPlane->deactivateLights();
    }
    if(state[SDL_SCANCODE_SPACE]){
        givenPlane->accel(deltaTime);
    }

    givenPlane->update(deltaTime);
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

    // Main shader implementation
    renderManage->predraw();

    glm::mat4 modelMatrix = glm::mat4x4(1.0f);
    glm::quat testQuat = glm::normalize(glm::quat(1.0f,0.0f,0.0f,0.0f));
    glm::quat test2Quat = glm::normalize(glm::quat(cos(u_rotate),0.0f,sin(u_rotate),0.0f));
    glm::quat test3Quat = testQuat * test2Quat;
    glm::mat4 rotationMatrix = glm::mat4_cast(test3Quat);
    glm::mat4 lightModelMatrix = glm::translate(modelMatrix, glm::vec3(u_offSet/5,-u_offSet/5,u_offSet));
    transformStore = Transform(glm::vec3(u_scale,u_scale,u_scale), glm::vec3(0.0f,0.0f,u_offSet), test3Quat);
    transformStore2 = Transform(glm::vec3(u_scale2,u_scale2,u_scale2), glm::vec3(0.0f,0.0f,u_offSet2), test3Quat * glm::normalize(glm::quat(cos(u_rotate),0.0f,sin(u_rotate),0.0f)));
    transformStore3 = Transform(glm::vec3(0.0f), glm::vec3(0.0f),  glm::normalize(glm::quat(cos(u_lightRot),0.0f,sin(u_lightRot),0.0f)));
    transformStore4 = Transform(glm::vec3(0.25f),  viewCam.getEyeLoc() + viewCam.getViewLocation() * u_lightFoward, glm::normalize(glm::quat(1.0f,0.0f,0.0f,0.0f)));
    transformStore5 = Transform(glm::vec3(0.25f),  glm::vec3(0.0f,0.0f,u_offSet) + glm::vec3(0.0f,0.0f,-1.0f) * glm::normalize(glm::quat(cos(u_lightOrbit) * (glm::sqrt(3)/glm::sqrt(4)),0.0f,sin(u_lightOrbit) * (glm::sqrt(3)/glm::sqrt(4)),-0.5f)), glm::normalize(glm::quat(1.0f,0.0f,0.0f,0.0f)));
    transformStore7 = Transform(glm::vec3(0.25f),  viewCam.getEyeLoc(), glm::normalize(glm::quat(cos(u_lightOrbit),0.0f,sin(u_lightOrbit),0.0f)));
    // Create transformation matrices
    glm::mat4 viewMatrix = viewCam.getViewMat();
    glm::mat4 perspectiveMatrix = glm::perspective(glm::radians(45.0f), (float)WINDOW_WIDTH/(float)WINDOW_HEIGHT, 0.1f, 10.0f);

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glViewport(0,0,WINDOW_WIDTH, WINDOW_HEIGHT);
    glClearColor(1.f, 1.f, 0.f, 1.f);
    glClear(GL_DEPTH_BUFFER_BIT| GL_COLOR_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    // Light shader implementations
    LightGraphicsPipeline->use();
    LightGraphicsPipeline->setMatrix("u_perspectiveMat", perspectiveMatrix);
    LightGraphicsPipeline->setMatrix("u_modelMat", lightModelMatrix);
    LightGraphicsPipeline->setMatrix("u_viewMat",viewMatrix);
}

void drawFunc(){
    renderManage->draw();
    
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
    SkyboxPipeline = new Shader(skyboxVertexShaderFileName, skyboxFragmentShaderFileName);
    GraphicsPipeline = new Shader(vertexShaderFileName, fragmentShaderFileName);
    LightGraphicsPipeline = new Shader(vertexShaderFileName, lightFragmentShaderFileName);
}

void VertexSpecification(){ 
    // Compiles into mesh
    GLCheck(renderManage = new RenderManager(&viewCam, glm::perspective(glm::radians(45.0f), (float)WINDOW_WIDTH/(float)WINDOW_HEIGHT, 0.1f, 80.0f), GraphicsPipeline, WINDOW_WIDTH, WINDOW_HEIGHT);)
    renderManage->setLightMap(skyFrontPath,skyRightPath,skyLeftPath,skyBackPath,skyBottomPath,skyTopPath, SkyboxPipeline);
    GLCheck(renderManage->insertModel(base,backpackPath);)
    GLCheck(renderManage->insertModel(base2,buildingPath);)
    GLCheck(renderManage->insertModel(base3,basePath);)
    GLCheck(renderManage->insertModel(base4,planePath);)
    GLCheck(modelOb = new ModelObject(&transformStore, 0, renderManage);)
    GLCheck(modelOb2 = new ModelObject(&transformStore2, 1, renderManage);)
    GLCheck(modelOb2 = new ModelObject(&transformStore9, 1, renderManage);)
    GLCheck(modelOb2 = new ModelObject(&transformStore8, 3, renderManage);)
    GLCheck(modelOb2 = new ModelObject(&transformStore6, 2, renderManage);)
    GLCheck(singleLight = new DirLightObject(&transformStore3, renderManage, glm::vec3(0.2f),glm::vec3(0.5f),glm::vec3(0.3f));)
    transformStore6 = Transform(glm::vec3(0.2f), glm::vec3(-1.0f), glm::quat(1.0f,0.0f,0.0f,0.0f));
    transformStore8 = Transform(glm::vec3(0.1f), glm::vec3(-1.0f), glm::normalize(glm::quat(1.0f,0.0f,-1.0f,0.0f)));
    givenPlane.reset(new Plane(&viewCam, renderManage, 3, 0.25, 0.5, 2.5, 6, 2.5, 0.5, glm::vec3(0.0f)));
    transformStore9 = Transform(glm::vec3(0.5f), glm::vec3(0.5f), glm::normalize(glm::quat(1.0f,0.0f,0.0f,0.0f)));
    transformStore9.setParent(&transformStore);

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
    renderManage->Quit();
    delete GraphicsPipeline;
    delete LightGraphicsPipeline;

    //Destroy window
    SDL_DestroyWindow(graphicsWindow);
    //Quit SDL subsystems
    SDL_Quit();
}

// Test
int main(){
    // Initializes SDL and OpenGL while opening window
    InitializeProgram();

    // Creates shaders, both fragment and vector
    CreateGraphicsPipeline();

    // Specifies VAO and VBO
    VertexSpecification();

    lastTime = SDL_GetTicks();
    deltaTime = 0;

    // Continually draws over file
    MainLoop();

    // Ends running subsystems
    CleanUp();

    return 0;
}
