//
// Created by Filip on 28.10.2023.
//

#ifndef TEST_SCENE_H
#define TEST_SCENE_H


#include "Shaders/ShaderProgramHolder.h"
#include "Camera.h"
#include "Light.h"
#include "Models/Shape.h"

#include <functional>
#include <memory>
#include <GLFW/glfw3.h>

using std::vector;

class Scene {
private:
    vector<unique_ptr<Shape>> shapes;
public:

    std::string title{"No title"};
    GLFWwindow* window;
    Camera camera;
    Light light{glm::vec3(-0,0,0), glm::vec3(0,0,-1), 360};

    ShaderProgramHolder* shaderProgramHolder;



    std::function<void(void)> preDraw{[](){}};//initialize values, so we don't get bad function call errors.
    std::function<void(void)> postDraw{[](){}};

    Shape* makeShape(const char *name, float x, float y, float z, ShaderProgram *shaderProgram);
    Shape* makeShape(const char *name, float x, float y, float z, const char* shaderName);

    void createShaderProgram(const char* name, const char* vertexFilepath, const char* fragmentFilepath);

    void initializeShaders(){
        shaderProgramHolder->forEach([this](ShaderProgram* shaderProgram){
            camera.addObserver(shaderProgram);
            light.addObserver(shaderProgram);
        });
        camera.notify();
        light.notify();
    }

    void drawModels();

    void setWindow(GLFWwindow* other);
};


#endif //TEST_SCENE_H
