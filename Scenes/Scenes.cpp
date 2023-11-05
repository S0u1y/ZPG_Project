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




