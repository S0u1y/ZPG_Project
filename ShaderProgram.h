//
// Created by wizzy on 16.10.23.
//

#ifndef TEST_SHADERPROGRAM_H
#define TEST_SHADERPROGRAM_H

#include <GL/glew.h>

#include <unordered_map>
#include <memory>


#include "Shader.h"

class ShaderProgram {
private:
    std::unordered_map<char*, std::shared_ptr<Shader>> shaders;

public:
    GLuint createShader(char* name, const char* vertexShader, const char* fragmentShader);
    Shader& getShader(char* name);
    void createAllShaders();
};


#endif //TEST_SHADERPROGRAM_H
