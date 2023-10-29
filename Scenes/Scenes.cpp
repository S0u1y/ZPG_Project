//
// Created by Filip on 28.10.2023.
//

#include "Scenes.h"
#include "../Composite/killmeplease.h"
#include "../Composite/Transformation/Rotation.h"
#include "../Composite/Transformation/Move.h"

void Scenes::initializeShaders() {
    shaderProgramHolder.createShader("MainShader", "main.vert", "main.frag");
    shaderProgramHolder.createShader("Gradient", "gradient.vert", "gradient.frag");
    shaderProgramHolder.createShader("Constant", "constant.vert", "constant.frag");
    shaderProgramHolder.createShader("Light", "lambert.vert", "lambert.frag");
    shaderProgramHolder.createShader("Phong", "phong.vert", "phong.frag");
    shaderProgramHolder.createShader("Blinn", "blinn.vert", "blinn.frag");
}

void Scenes::initialize() {
    initializeShaders();
    auto sceneA = new Scene();
    this->scenes.emplace("Scene1", sceneA);
    auto sceneB = new Scene();
    scenes.emplace("Scene2", sceneB);



    for (const auto &item : scenes){
        item.second->shaderProgramHolder = &shaderProgramHolder;
    }


    sceneA->makeShape("sphere", 1.5, 0, 0, "Phong");
    sceneA->makeShape("sphere", -1.5, 0, 0, "Phong");
    sceneA->makeShape("sphere", 0, 1.5, 0, "Phong");
    sceneA->makeShape("sphere", 0, -1.5, 0, "Phong");


    sceneB->camera.moveY(5);

    auto sun = sceneB->makeShape("sphere", 0, 0, 0, "Constant");
    sun->scale(glm::vec3(2,2,2));
//    sceneB->makeShape("sphere", -1.5, 0, 0, "Light");

    auto planet = sceneB->makeShape("sphere", 0, 0, 0, "Light");
    auto planet2 = sceneB->makeShape("sphere", 0, 0, 0, "Light");
//    planet->scale(glm::vec3(.5,.5,.5));
    planet2->scale(glm::vec3(.5,.5,.5));

    killmeplease kms;
    kms.shapes.push_back(planet);
    kms.shapes.push_back(planet2);

    kms.Add(new Rotation(.01, glm::vec3(0,1,0)));
    kms.Add(new Move(glm::vec3(0,0,5)));
    sceneB->preDraw = [=](){
    };
    sceneB->postDraw = [=](){
    };
}

Scene *Scenes::operator[](const char* name) {
    for (const auto &item : scenes){
        if (strcmp(item.first, name) == 0){
            return item.second.get();
        }
    }

    printf("%s not found in scenes.\n", name);
    exit(-1);
    return nullptr;
}




