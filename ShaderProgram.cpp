//
// Created by wizzy on 16.10.23.
//

#include "ShaderProgram.h"

void ShaderProgram::createShader(char* name, const char *vertexShader, const char *fragmentShader) {

    shaders.emplace(name, new Shader(vertexShader, fragmentShader));

}

Shader &ShaderProgram::getShader(char *name) {
    return *shaders[name].get();
}

void ShaderProgram::createAllShaders() {
    for (const auto &item: shaders){
        item.second->create();
    }
}

Shader *ShaderProgram::getShaderp(char *name) {
    return shaders[name].get();
}
