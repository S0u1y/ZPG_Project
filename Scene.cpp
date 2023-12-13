//
// Created by Filip on 28.10.2023.
//

#include "Scene.h"

#include <memory>

#include "Factory/ModelFactory.h"
#include "CameraLight.h"


Shape *Scene::makeShape(Shape *shape, const char *shaderName) {
    shape->setShader(shaderProgramHolder->getShaderp(shaderName));
    shapes.push_back(std::unique_ptr<Shape>(shape));
    return shapes[shapes.size()-1].get();
}

Shape* Scene::makeShape(const char *name, float x, float y, float z, ShaderProgram* shaderProgram) {
    auto newModel = std::unique_ptr<Shape>(ModelFactory::createModel(name, x, y, z));
    newModel->setShader(shaderProgram);
    shapes.push_back(std::move(newModel));
    return shapes[shapes.size()-1].get();
}

Shape* Scene::makeShape(const char *name, float x, float y, float z, const char *shaderName) {
    return makeShape(name, x, y, z, shaderProgramHolder->getShaderp(shaderName));
}

void Scene::updateShaders() {
    if(shadersInitialized){
        //put this into observer?
        shaderProgramHolder->forEach([this](ShaderProgram* program){
            program->setUniform("lightSources_n", (int)lights.size());//update number of lights in all shaders...
        });
    }
}

Light *Scene::makeLight(glm::vec3 position, glm::vec3 direction, float angle) {
    lights.push_back(std::make_unique<Light>(position, direction, angle));
    auto output = lights[lights.size()-1].get();//get the last added light pointer from vector
    output->id = lights.size()-1;

    //observers are added after all of this is called usually.
    //TODO make every shader unique and also make observers unique so they're not added twice
//    if(shadersInitialized){
//        shaderProgramHolder->forEach([=](ShaderProgram* program){
//            output->addObserver(program);
//        });
//        output->notify();
//    }

    updateShaders();
    return output;
}

Light *Scene::makeCameraLight(float angle) {
    lights.push_back(std::unique_ptr<Light>(new CameraLight({0,0,0},{0,0,0}, angle)));
    auto output = lights[lights.size()-1].get();
    output->id = lights.size()-1;

    camera.addObserver((CameraLight*)output);

    updateShaders();
    return output;
}

Light* Scene::addLight(DirectionalLight* light) {
    this->lights.push_back(unique_ptr<Light>(light));
    auto output = lights[lights.size()-1].get();
    output->id = lights.size()-1;

    if(shadersInitialized){
        shaderProgramHolder->forEach([&output](ShaderProgram* program){
            output->addObserver(program);
        });
        output->notify();
    }

    updateShaders();
    return output;
}

void Scene::createShaderProgram(const char* name, const char* vertexFilepath, const char* fragmentFilepath) {
    shaderProgramHolder->createShader(name, vertexFilepath, fragmentFilepath);
}

void Scene::drawModels() {
    preDraw();
//    for (const auto &item : shapes){
//
//        item->draw();
//    }
    for (int i = 0; i < shapes.size(); i++) {
        //stencil buffer clears every frame
        //also it wouldn't align if we move camera
        //so write into it every frame
        glStencilFunc(GL_ALWAYS, i+1, 0xFF);
        shapes[i]->draw();

    }
    postDraw();
}

void Scene::setWindow(GLFWwindow *other) {
    this->window = other;
    glfwSetWindowTitle(window, title.c_str());
}

void Scene::initializeShaders() {
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

void Scene::setModelFactoryMode(bool mode) {
    ModelFactory::setTextured(mode);
}










