//
// Created by Filip on 28.10.2023.
//

#include "Scenes.h"
#include "../Composite/killmeplease.h"
#include "../Composite/Transformation/Rotation.h"
#include "../Composite/Transformation/Move.h"

#include <random>

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
    scenes.emplace("Scene1", sceneA);
    auto sceneB = new Scene();
    scenes.emplace("Scene2", sceneB);
    auto sceneC = new Scene();
    scenes.emplace("Scene3", sceneC);


    for (const auto &item : scenes){
        item.second->shaderProgramHolder = &shaderProgramHolder;
    }

    //SCENE 1
    sceneA->makeShape("sphere", 1.5, 0, 0, "Phong");
    sceneA->makeShape("sphere", -1.5, 0, 0, "Phong");
    sceneA->makeShape("sphere", 0, 1.5, 0, "Phong");
    sceneA->makeShape("sphere", 0, -1.5, 0, "Phong");

    sceneA->camera.setEye({0,0,5});
    sceneA->camera.setTarget({0,0,-1});

    //SCENE 2
    sceneB->title = "Slunecni soustava";
    sceneB->camera.moveY(5);

    auto sun = sceneB->makeShape("sphere", 0, 0, 0, "Constant");
    sun->scale(glm::vec3(2,2,2));
    sun->material.color = {.75,.75,0};

    auto planet = sceneB->makeShape("sphere", 0, 0, 0, "Light");
    auto planet2 = sceneB->makeShape("sphere", 0, 0, 0, "Light");
    auto planet3 = sceneB->makeShape("sphere", 0,0,0, "Phong");


    auto* kms = new killmeplease();
//    auto* kms2 = new killmeplease();

    kms->shapes.push_back(planet);
    kms->shapes.push_back(planet2);
    kms->shapes.push_back(planet3);

    composites.push_back(shared_ptr<killmeplease>(kms));


    sceneB->preDraw = [=](){
        auto time = (float)glfwGetTime();

        kms->Add(new Rotation(0.01, {0,1,0}));
        kms->Add(new Move({0,0,10}));
        kms->action();

        planet2->scale({.5,.5,.5});
        planet2->rotate( 0.5f, { 0, 1, 0 });
        planet2->move(0,0,5);
        planet2->rotate( 1.f, { 0, 1, 0 });

        planet3->scale({.25,.25,.25});
        planet3->rotate(time * 0.75f, { 0, 1, 0 });
        planet3->move(0,0,7);

    };
    sceneB->postDraw = [=](){

        kms->Add(new Move({0,0,-10}));
    };

    //SCENE 3

    sceneC->title = "Les";

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> dist(-100.f, 100.0);

    for(int i = 0; i < 50; i++){
        auto x = dist(mt);
        auto z = dist(mt);

        auto tree = sceneC->makeShape("tree", x, 0, z, "Constant");
        tree->material.color = {0,0.5,0};
        tree->rotate(glm::radians(36.f),{0,1,0});
    }
    for(int i = 0; i < 50; i++){
        auto x = dist(mt);
        auto z = dist(mt);

        auto bush = sceneC->makeShape("bushes", x, 0, z, "Constant");
        bush->material.color = {0,0.1,0};
        bush->rotate(glm::radians(36.f),{0,1,0});
    }

    auto plain = sceneC->makeShape("plain", 0, 0, 0, "Constant");
    plain->material.color = {0, 0.12, 0};
    plain->scale({150, 0, 150});


    sceneC->camera.setEye({0,2,5});
    sceneC->camera.setTarget({0,0,-1});
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




