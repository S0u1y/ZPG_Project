//
// Created by wizzy on 25.10.23.
//

#include "ShaderProgramHolder.h"


void ShaderProgramHolder::createShader(const char* name, Shader vertexShader, Shader fragmentShader) {

    shaders.emplace(name, new ShaderProgram(vertexShader, fragmentShader));

}

void ShaderProgramHolder::createShader(const char* name, ShaderProgram* shaderProgram) {
    shaders.emplace(name, shaderProgram);
}

void ShaderProgramHolder::createShader(const char *name,const char *vertexShaderFilepath,const char *fragmentShaderFilepath) {
    shaders.emplace(name, new ShaderProgram(vertexShaderFilepath, fragmentShaderFilepath));
}

ShaderProgram &ShaderProgramHolder::getShader(const char *name) {
    return *this->operator[](name);
}

void ShaderProgramHolder::createAllShaders() {
}

ShaderProgram *ShaderProgramHolder::getShaderp(const char *name) {
    for (const auto &item : shaders){
        if(!strcmp(item.first, name)){
            return item.second.get();
        }
    }

    printf("%s not found in shaders.\n", name);
    exit(-1);
    return nullptr;
}

void ShaderProgramHolder::forEach(const std::function<void(ShaderProgram*)>& func) {
    for (const auto &item : shaders){
        func(item.second.get());
    }
}

ShaderProgram *ShaderProgramHolder::operator[](const char *name) {
    for (const auto &item : shaders){
        if(!strcmp(item.first, name)){
            return item.second.get();
        }
    }

    printf("%s not found in shaders.\n", name);
    exit(-1);
    return nullptr;
}








