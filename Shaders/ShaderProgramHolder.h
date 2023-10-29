//
// Created by wizzy on 25.10.23.
//

#ifndef TEST_SHADERPROGRAMHOLDER_H
#define TEST_SHADERPROGRAMHOLDER_H


#include <unordered_map>
#include <memory>
#include "ShaderProgram.h"

#include <functional>

class ShaderProgramHolder {
private:

public:
    std::unordered_map<const char*, std::shared_ptr<ShaderProgram>> shaders;
    void createShader(const char* name, Shader vertexShader, Shader fragmentShader);
    void createShader(const char* name, ShaderProgram* shaderProgram);
    void createShader(const char* name,const char* vertexShaderFilepath,const char* fragmentShaderFilepath);
    ShaderProgram& getShader(const char* name);
    ShaderProgram* getShaderp(const char* name);
    ShaderProgram* operator[](const char* name);
    void createAllShaders();
    void forEach(const std::function<void(ShaderProgram*)>& func);
    //TODO add unbind func
};


#endif //TEST_SHADERPROGRAMHOLDER_H
