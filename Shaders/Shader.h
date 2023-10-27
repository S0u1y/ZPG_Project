//
// Created by wizzy on 25.10.23.
//

#ifndef TEST_SHADER_H
#define TEST_SHADER_H


#include <GL/glew.h>
#include <string>

class Shader {
public:
    const char* filepath;

    explicit Shader(const char *filepath);
    Shader(){};
};


#endif //TEST_SHADER_H
