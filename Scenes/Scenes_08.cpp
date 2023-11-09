//
// Created by Filip on 07.11.2023.
//

#include "Scenes_08.h"

void Scenes_08::initializeShaders() {
    Scenes::initializeShaders();
}

void Scenes_08::initialize() {
    Scenes::initialize();

    auto sceneA = new Scene();
    scenes.emplace("Scene1", sceneA);

    for (const auto &item : scenes){
        item.second->shaderProgramHolder = &shaderProgramHolder;
    }

    sceneA->camera.setEye({0,0,5});
    sceneA->camera.setTarget({0,0,-1});

    sceneA->lights[0]->constant = 50;

    auto light = sceneA->addLight(new DirectionalLight({0,2,0}, {0,1,-1}, 360));

    light->constant = 1;
    light->quadratic = 0;
    light->linear = 0;
//    sceneA->makeCameraLight(6);
    auto sphere = sceneA->makeShape("sphere", 0, -1.5, 0, "Phong");
    sphere->material.r_s = 0;
    sphere->material.r_d = 0.5;
    auto sphere2 = sceneA->makeShape("sphere", -3, -1.5, 0, "Phong");
    sphere2->material.r_s = 1;
    sphere2->material.r_d = 0.5;
}
