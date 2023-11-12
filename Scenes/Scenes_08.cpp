//
// Created by Filip on 07.11.2023.
//

#include "Scenes_08.h"
#include "SOIL.h"
#include "../Models/TextureModel.h"

void Scenes_08::initializeShaders() {
    Scenes::initializeShaders();
    shaderProgramHolder.createShader("BasicTextured", "BasicTexture.vert", "BasicTexture.frag");
}

void Scenes_08::initialize() {
    initializeShaders();
    {
        auto sceneA = createScene("Scene1");

        sceneA->camera.setEye({0,0,5});
        sceneA->camera.setTarget({0,0,-1});

        sceneA->lights[0]->constant = 50;

        auto cameraLight = sceneA->makeCameraLight(15);
        cameraLight->constant = 1;
        cameraLight->linear = 0;
        cameraLight->quadratic = 0;

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

        auto suzi = sceneA->makeShape("suzi_smooth", 0, 3, 0, "Phong");
        suzi->rotate(glm::radians(180.f), {0,1,0});
    }

    {
        auto scene = createScene("Scene2");

        scene->setModelFactoryMode(true);
        auto plain = scene->makeShape("plain", 0, -1.5, 0, "BasicTextured");
        ((TextureModel*)plain)->textureID = 0;
        scene->setModelFactoryMode(false);

        plain->rotate(glm::radians(90.f), {1,0,0});

        scene->preDraw = [=]{
        };

    }


}
