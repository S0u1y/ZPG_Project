//
// Created by Filip on 07.11.2023.
//

#include <random>
#include "Scenes_08.h"
#include "../Models/NoTextureModel.h"
#include "../Models/TextureModel.h"
#include "../Textures/TextureHolder.h"
#include "../Models/CubemapModel.h"
#include "../Textures/CubemapTexture.h"
#include "../ModelLoader.h"
#include "../Models/ModelVisitor.h"
#include "../Models/ModelVerticesHolder.h"
//#include "../Models/ModelVisitor.h"

void Scenes_08::initializeShaders() {
    Scenes::initializeShaders();
    shaderProgramHolder.createShader("BasicTextured", "BasicTexture.vert", "BasicTexture.frag");
    shaderProgramHolder.createShader("SkyCube", "cubemap.vert", "cubemap.frag");
}

void Scenes_08::initialize() {
    initializeShaders();
    initializeTextures();
    initializeModelVertices();

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
    {
        auto scene = createScene("Scene3");

        scene->lights[0]->constant = 3;

        scene->camera.setEye({0,2,5});
        scene->camera.setTarget({0,0,-1});

        scene->setModelFactoryMode(true);
        auto skycube = scene->makeShape("skycube", 0,0,0, "SkyCube");
//        skycube->scale({1,1,1});
        auto ptr = (TextureHolder::getInstance())->operator[]("skycube");
        ((CubemapModel*)skycube)->textureID = ((CubemapTexture*)ptr)->getTextureUnit();


        auto plain = scene->makeShape("plain", 0, 0, 0, "BasicTextured");
        plain->rotate(glm::radians(90.f), {1,0,0});//why do I have to rotate it?
        plain->scale({100, 100, 100});
        auto grass_texture = TextureHolder::getInstance()->operator[]("grass");
        ((TextureModel*)plain)->textureID = grass_texture->getTextureUnit();

//        grass_texture->activate();
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
//        grass_texture->unbind();

        scene->setModelFactoryMode(false);



        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_real_distribution<float> dist(-50.f, 50.0);
        std::uniform_real_distribution<float> dist2(0.25, 5);
        for(int i = 0; i < 50; i++){
            auto x = dist(mt);
            auto z = dist(mt);

            auto scale = dist2(mt);

            auto tree = scene->makeShape("tree", x, 0, z, "Phong");
            tree->material.color = {0,0.5,0};
            tree->rotate(glm::radians(36.f),{0,1,0});
            tree->scale({scale,scale,scale});
        }
        for(int i = 0; i < 50; i++){
            auto x = dist(mt);
            auto z = dist(mt);

            auto scale = dist2(mt);

            auto bush = scene->makeShape("bushes", x, 0, z, "Constant");
            bush->material.color = {0,0.1,0};
            bush->rotate(glm::radians(36.f),{0,1,0});
            bush->scale({scale,scale,scale});
        }


    }
    {
        auto scene = createScene("Object");
        scene->lights[0]->move({0,10,0});
        scene->camera.setEye({0, 5, -5});
        static auto vertices = ModelLoader::getVertices("../Models/Sources/house.obj");
        auto newModel = new TextureModel(0, 0, 0, vertices.data(), vertices.size());
        CreateModelVisitor visitor;
        newModel->accept(visitor);
        ((TextureModel*)newModel)->textureID = TextureHolder::getInstance()->operator[]("model")->getTextureUnit();
//        newModel->setShader(shaderProgramHolder.getShaderp("Phong"));
        scene->makeShape(newModel, "BasicTextured");
    }
    {
        auto scene = createScene("Zidle");
        static auto vertices = ModelVerticesHolder::getVerticesAt("wooden_chair");
        auto zidle = new TextureModel(0, 0, 0, vertices.data(), vertices.size());
        CreateModelVisitor visitor;
        zidle->accept(visitor);
        ((TextureModel*)zidle)->textureID = TextureHolder::getInstance()->operator[]("wooden_chair")->getTextureUnit();
        scene->makeShape(zidle, "BasicTextured");

        zidle->rotate(glm::radians(-90.f), {1,0,0});

        auto zidle2 = new TextureModel(0, 0, -5, vertices.data(), vertices.size());
        zidle2->accept(visitor);
        ((TextureModel*)zidle2)->textureID = TextureHolder::getInstance()->operator[]("wooden_chair")->getTextureUnit();
        scene->makeShape(zidle2, "BasicTextured");


//        scene->preDraw = [zidle]{
//            zidle->rotate(glm::radians(1.f), {0,0,1});
//        };

    }


}
//probably will crash.. opengl needs to be initialized before this.
void Scenes_08::initializeTextures() {
    Scenes::initializeTextures();
}
