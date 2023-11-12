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

#include "DirectionalLight.h"

using std::vector;

class Scene {
private:
    bool shadersInitialized = false;
    vector<unique_ptr<Shape>> shapes;

    void updateShaders();
public:

    std::string title{"No title"};
    GLFWwindow* window;
    Camera camera;
    vector<unique_ptr<Light>> lights;


    ShaderProgramHolder* shaderProgramHolder;



    std::function<void(void)> preDraw{[](){}};//initialize values, so we don't get bad function call errors.
    std::function<void(void)> postDraw{[](){}};

    //TODO add functionality to remove lights as well.

    Scene(){
        makeLight(glm::vec3(0,0,0), glm::vec3(0,0,0), 360);
    }

    void setModelFactoryMode(bool mode);
    Shape* makeShape(const char *name, float x, float y, float z, ShaderProgram *shaderProgram);
    Shape* makeShape(const char *name, float x, float y, float z, const char* shaderName);
    Light* makeLight(glm::vec3 position, glm::vec3 direction, float angle);
    Light* makeCameraLight(float angle);

    Light* addLight(DirectionalLight* light);

    void createShaderProgram(const char* name, const char* vertexFilepath, const char* fragmentFilepath);

    //TODO add loading textures..
    void initializeShaders();

    void drawModels();

    void setWindow(GLFWwindow* other);
};


#endif //TEST_SCENE_H
