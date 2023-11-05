//
// Created by Filip on 28.10.2023.
//

#include "Scene.h"

#include "Factory/ModelFactory.h"

Shape* Scene::makeShape(const char *name, float x, float y, float z, ShaderProgram* shaderProgram) {
    auto newModel = std::unique_ptr<Shape>(ModelFactory::createModel(name, x, y, z));
    newModel->setShader(shaderProgram);
    shapes.push_back(std::move(newModel));
    return shapes[shapes.size()-1].get();
}

Shape* Scene::makeShape(const char *name, float x, float y, float z, const char *shaderName) {
    return makeShape(name, x, y, z, shaderProgramHolder->getShaderp(shaderName));
}

Light *Scene::makeLight(glm::vec3 position, glm::vec3 direction, float angle) {
    lights.push_back(std::unique_ptr<Light>(new Light(position, direction, angle)));//move the pointer inside the lights vector
    auto output = lights[lights.size()-1].get();//get the last added light pointer from vector
    output->id = lights.size()-1;

//    if(shadersInitialized){
//        shaderProgramHolder->forEach([=](ShaderProgram* program){
//            output->addObserver(program);
//        });
//        output->notify();
//    }

    if(shadersInitialized){
        //put this into observer?
        shaderProgramHolder->forEach([this](ShaderProgram* program){
            program->setUniform("lightSources_n", (int)lights.size());//update number of lights in all shaders...
        });
    }

    return output;
}

void Scene::createShaderProgram(const char* name, const char* vertexFilepath, const char* fragmentFilepath) {
    shaderProgramHolder->createShader(name, vertexFilepath, fragmentFilepath);
}

void Scene::drawModels() {
    preDraw();
    for (const auto &item : shapes){
        item->draw();
    }
    postDraw();
}

void Scene::setWindow(GLFWwindow *other) {
    this->window = other;
    glfwSetWindowTitle(window, title.c_str());
}


