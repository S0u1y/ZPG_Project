//
// Created by wizzy on 25.10.23.
//

#include "ShaderProgramHolder.h"


void ShaderProgramHolder::createShader(char* name, Shader vertexShader, Shader fragmentShader) {

    shaders.emplace(name, new ShaderProgram(vertexShader, fragmentShader));

}

void ShaderProgramHolder::createShader(char* name, ShaderProgram* shaderProgram) {
    shaders.emplace(name, shaderProgram);
}


ShaderProgram &ShaderProgramHolder::getShader(char *name) {
    return *shaders[name].get();
}

void ShaderProgramHolder::createAllShaders() {
}

ShaderProgram *ShaderProgramHolder::getShaderp(char *name) {
    return shaders[name].get();;
}



