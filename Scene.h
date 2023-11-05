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
    bool shadersInitialized = false;
    vector<unique_ptr<Shape>> shapes;
public:

    std::string title{"No title"};
    GLFWwindow* window;
    Camera camera;
    vector<unique_ptr<Light>> lights;


    ShaderProgramHolder* shaderProgramHolder;



    std::function<void(void)> preDraw{[](){}};//initialize values, so we don't get bad function call errors.
    std::function<void(void)> postDraw{[](){}};

    Scene(){
        makeLight(glm::vec3(-0,0,0), glm::vec3(0,0,-1), 360);
    }

    Shape* makeShape(const char *name, float x, float y, float z, ShaderProgram *shaderProgram);
    Shape* makeShape(const char *name, float x, float y, float z, const char* shaderName);
    Light* makeLight(glm::vec3 position, glm::vec3 direction, float angle);

    void createShaderProgram(const char* name, const char* vertexFilepath, const char* fragmentFilepath);

    void initializeShaders(){
        shadersInitialized = true;

        auto it = shaderProgramHolder->shaders.begin();
        shaderProgramHolder->forEach([this, &it](ShaderProgram* shaderProgram){
            camera.addObserver(shaderProgram);
            for (const auto &item: lights){
                item->addObserver(shaderProgram);
            }
//            if(shaderProgram->getUniform("lightSources[0].lightPosition") < 0){
//                printf("No multiple LightSources defined for shader %s.\n", (*it).first);
//            }
            shaderProgram->setUniform("lightSources_n", (int)lights.size());
            it++;
        });
        camera.notify();
        for (const auto &item: lights){
            item->notify();
        }
    }

    void drawModels();

    void setWindow(GLFWwindow* other);
};


#endif //TEST_SCENE_H
