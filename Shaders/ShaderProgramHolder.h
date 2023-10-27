//
// Created by wizzy on 25.10.23.
//

#ifndef TEST_SHADERPROGRAMHOLDER_H
#define TEST_SHADERPROGRAMHOLDER_H


#include <unordered_map>
#include <memory>
#include "ShaderProgram.h"

class ShaderProgramHolder {
private:
    std::unordered_map<char*, std::shared_ptr<ShaderProgram>> shaders;

public:
    void createShader(char* name, Shader vertexShader, Shader fragmentShader);
    void createShader(char* name, ShaderProgram* shaderProgram);
    ShaderProgram& getShader(char* name);
    ShaderProgram* getShaderp(char* name);
    void createAllShaders();
};


#endif //TEST_SHADERPROGRAMHOLDER_H
