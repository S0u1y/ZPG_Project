//
// Created by Filip on 28.10.2023.
//

#include "Scenes.h"

#include "../Textures/TextureHolder.h"

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

Scene *Scenes::createScene(const char *name) {
    auto pair = scenes.emplace(name, new Scene);
    if(pair.second){//second from returned pair is whether it has been added or not.
        pair.first->second->shaderProgramHolder = &shaderProgramHolder;
        return pair.first->second.get();
    }
    return nullptr;//maybe instead of nullptr, make the program exit here?
}

void Scenes::initializeTextures() {
    std::string sourcesP = "../Textures/Sources/";
    TextureHolder::createTexture("wood_planks", (sourcesP + "wooden_fence.png").c_str(), GL_TEXTURE_2D);
    TextureHolder::createCubemap("skycube", sourcesP + "posx.jpg", sourcesP + "negx.jpg", sourcesP + "posy.jpg",
                                 sourcesP + "negy.jpg", sourcesP + "posz.jpg", sourcesP + "negz.jpg", GL_TEXTURE_2D);
    TextureHolder::createTexture("grass", (sourcesP + "grass.png").c_str(), GL_TEXTURE_2D);
}




