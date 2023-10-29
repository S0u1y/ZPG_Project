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
