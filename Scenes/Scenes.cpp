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

    //SCENE 1
    sceneA->makeShape("sphere", 1.5, 0, 0, "Phong");
    sceneA->makeShape("sphere", -1.5, 0, 0, "Phong");
    sceneA->makeShape("sphere", 0, 1.5, 0, "Phong");
    sceneA->makeShape("sphere", 0, -1.5, 0, "Phong");



    //SCENE 2
    sceneB->camera.moveY(5);

    auto sun = sceneB->makeShape("sphere", 0, 0, 0, "Constant");
    sun->scale(glm::vec3(2,2,2));

    auto planet = sceneB->makeShape("sphere", 0, 0, 0, "Light");
    auto planet2 = sceneB->makeShape("sphere", 0, 0, 0, "Light");
    auto planet3 = sceneB->makeShape("sphere", 0,0,0, "Phong");


    auto* kms = new killmeplease();
    kms->shapes.push_back(planet);
    kms->shapes.push_back(planet2);
    kms->shapes.push_back(planet3);

    composites.push_back(shared_ptr<killmeplease>(kms));


    sceneB->preDraw = [=](){
        auto time = (float)glfwGetTime();

//        planet->rotate(.01, { 0, 1, 0 });
//        planet->move(0,0,5);
//
//        planet->performTransformation();
//        planet2->transformation = planet->transformation;

        kms->Add(new Rotation(0.01, {0,1,0}));
        kms->Add(new Move({0,0,10}));
        kms->action();

        planet2->scale({.5,.5,.5});
        planet2->rotate(time * 0.5f, { 0, 1, 0 });
        planet2->move(0,0,5);

//        planet3->scale({.25,.25,.25});
        planet3->rotate(time * 0.75f, { 0, 1, 0 });
        planet3->move(0,0,7);

    };
    sceneB->postDraw = [=](){
//        planet->move(0,0,-5);

        kms->Add(new Move({0,0,-10}));
//        planet2->move(0,0,-5);
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




