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
    auto sceneD = new Scene();
    scenes.emplace("Scene3", sceneD);
    auto sceneE = new Scene();
    scenes.emplace("Scene4", sceneE);
    auto sceneC = new Scene();
    scenes.emplace("Scene5", sceneC);


    for (const auto &item : scenes){
        item.second->shaderProgramHolder = &shaderProgramHolder;
    }

    //SCENE 1
    sceneA->camera.setEye({0,0,5});
    sceneA->camera.setTarget({0,0,-1});
    sceneA->light.a = 3;
    sceneA->light.b = 0.7;

    sceneA->makeShape("sphere", 1.5, 0, 0, "Phong");
    sceneA->makeShape("sphere", -1.5, 0, 0, "Phong");
    sceneA->makeShape("sphere", 0, 1.5, 0, "Phong");
    sceneA->makeShape("sphere", 0, -1.5, 0, "Phong");



    //SCENE 2
    sceneB->title = "Slunecni soustava";
    sceneB->camera.moveY(5);
//    sceneB->light.setLightColor({0.5,0.5,0});
    sceneB->light.a = 0.001;
    sceneB->light.b = 0.001;

    auto sun = sceneB->makeShape("sphere", 0, 0, 0, "Constant");
    sun->scale(glm::vec3(2,2,2));
    sun->material.color = {.75,.75,0};

    auto merkur = sceneB->makeShape("sphere", 0, 0, 0, "Light");
    merkur->scale({.5,.5,.5});
    auto venus = sceneB->makeShape("sphere", 0, 0, 0, "Light");
    venus->scale({.9,.9,.9});
    auto earth = sceneB->makeShape("sphere", 0, 0, 0, "Light");
    auto moon = sceneB->makeShape("sphere", 0, 0, 0, "Light");
    auto mars = sceneB->makeShape("sphere", 0, 0, 0, "Light");
    auto mars_moon_one = sceneB->makeShape("sphere", 0, 0, 0, "Light");
    auto mars_moon_two = sceneB->makeShape("sphere", 0, 0, 0, "Light");
    auto jupiter = sceneB->makeShape("sphere", 0, 0, 0, "Light");
    auto jupiter_moon1 = sceneB->makeShape("sphere", 0, 0, 0, "Light");
    auto jupiter_moon2 = sceneB->makeShape("sphere", 0, 0, 0, "Light");
    auto jupiter_moon3 = sceneB->makeShape("sphere", 0, 0, 0, "Light");
    auto jupiter_moon4 = sceneB->makeShape("sphere", 0, 0, 0, "Light");

    auto earthOrbit = new killmeplease();
    earthOrbit->shapes.push_back(earth);
    earthOrbit->shapes.push_back(moon);

    auto marsOrbit = new killmeplease();
    marsOrbit->shapes.push_back(mars);
    marsOrbit->shapes.push_back(mars_moon_one);
    marsOrbit->shapes.push_back(mars_moon_two);

    auto jupiterOrbit = new killmeplease();
    jupiterOrbit->shapes.push_back(jupiter);
    jupiterOrbit->shapes.push_back(jupiter_moon1);
    jupiterOrbit->shapes.push_back(jupiter_moon2);
    jupiterOrbit->shapes.push_back(jupiter_moon3);
    jupiterOrbit->shapes.push_back(jupiter_moon4);

//    composites.push_back(shared_ptr<killmeplease>(kms));


    sceneB->preDraw = [=](){
        auto time = (float)glfwGetTime();

        earthOrbit->Add(new Rotation(0.015, {0,1,0}));
        earthOrbit->Add(new Move({0,0,25}));
        earthOrbit->action();

        marsOrbit->Add(new Rotation(0.008, {0,1,0}));
        marsOrbit->Add(new Move({0,0,40}));
        marsOrbit->action();

        jupiterOrbit->Add(new Rotation(0.01, {0,1,0}));
        jupiterOrbit->Add(new Move({0,0,60}));
        jupiterOrbit->action();


        merkur->rotate(0.05, {0,1,0});
        merkur->move(0,0,15);

        venus->rotate(0.025, {0,1,0});
        venus->move(0,0,15);

        moon->scale({.5,.5,.5});
        moon->rotate(time * 0.75f, { 0, 1, 0 });
        moon->move(0,0,7);

        mars_moon_one->scale({.25,.25,.25});
        mars_moon_one->rotate(time * 0.75f, { 0, 1, 0 });
        mars_moon_one->move(0,0,7);

        mars_moon_two->scale({.15,.15,.15});
        mars_moon_two->rotate(time * 0.50f, { 0, 1, 0 });
        mars_moon_two->move(0,0,7);

        jupiter->scale({2.5,2.5,2.5});

        jupiter_moon1->rotate(time * 0.250f, { 0, 1, 0 });
        jupiter_moon1->move(0,0,2);
        jupiter_moon1->scale({.05,.05,.05});

        jupiter_moon2->rotate(time * 0.50f, { 0, 1, 0 });
        jupiter_moon2->move(0,0,3);
        jupiter_moon2->scale({.15,.15,.15});

        jupiter_moon3->rotate(time * 0.50f, { 0, 1, 0 });
        jupiter_moon3->move(0,0,2);
        jupiter_moon3->scale({.15,.15,.15});

        jupiter_moon4->rotate(time * 0.50f, { 0, 1, 0 });
        jupiter_moon4->move(0,0,4);
        jupiter_moon4->scale({.15,.15,.15});

    };
    sceneB->postDraw = [=](){
        earthOrbit->Add(new Move({0,0,-25}));
        marsOrbit->Add(new Move({0,0,-40}));
        jupiterOrbit->Add(new Move({0,0,-60}));

        merkur->move(0,0,-15);
        venus->move(0,0,-15);

    };

    //SCENE 3

    sceneD->title = "Orez svetla";

    sceneD->camera.setEye({0,0,3});
    sceneD->camera.setTarget({0,0,-1});

    sceneD->makeShape("sphere", 0, 0, 1.5, "Phong");

    //SCENE 4

    sceneE->title = "Zmena obrazovky";

    sceneE->light.a = 3;
    sceneE->light.b = 0.7;

    sceneE->makeShape("sphere", 1.5, 0, 0, "Phong");
    sceneE->makeShape("suzi_flat", -1.5, 0, 0, "Phong");
    sceneE->makeShape("suzi_smooth", 0, 1.5, 0, "Phong");
    sceneE->makeShape("gift", 0, -1.5, 0, "Phong");


    //SCENE 5

    sceneC->title = "Les";

    sceneC->light.move({0,50,0});
    sceneC->light.a = 0.001;
    sceneC->light.b = 0.001;

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> dist(-50.f, 50.0);
    std::uniform_real_distribution<float> dist2(0.25, 5);
    for(int i = 0; i < 50; i++){
        auto x = dist(mt);
        auto z = dist(mt);

        auto scale = dist2(mt);

        auto tree = sceneC->makeShape("tree", x, 0, z, "Phong");
        tree->material.color = {0,0.5,0};
        tree->rotate(glm::radians(36.f),{0,1,0});
        tree->scale({scale,scale,scale});
    }
    for(int i = 0; i < 50; i++){
        auto x = dist(mt);
        auto z = dist(mt);

        auto scale = dist2(mt);

        auto bush = sceneC->makeShape("bushes", x, 0, z, "Constant");
        bush->material.color = {0,0.1,0};
        bush->rotate(glm::radians(36.f),{0,1,0});
        bush->scale({scale,scale,scale});
    }

    auto plain = sceneC->makeShape("plain", 0, 0, 0, "Constant");
    plain->material.color = {0, 0.12, 0};
    plain->scale({150, 0, 150});

    auto gift = sceneC->makeShape("gift", 0, 0, 0, "Light");
    gift->material.color = {0.6,0,0};

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




