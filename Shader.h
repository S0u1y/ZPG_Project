//
// Created by wizzy on 27.9.23.
//

#ifndef TEST_SHADER_H
#define TEST_SHADER_H

#include <GL/glew.h>

#include <vector>
#include <cstdio>

#include <string>

#include <glm/ext/matrix_float4x4.hpp>

using std::vector;

class Camera;

class Shader {
private:
    const char* vertex_shader;

    const char* fragment_shader;

    GLuint vertexShader{};
    GLuint fragmentShader{};
    GLuint shaderProgram{};

    Camera* camera;

public:
    Shader(Camera* camera) : camera(camera)
    {
    }
    Shader(){};

    Shader(const char* vertexShader, const char* fragmentShader)
    : vertex_shader(vertexShader), fragment_shader(fragmentShader)
    {}

    void linkCamera(Camera* camera){
        this->camera = camera;
    }

    GLuint create();

    void useShader();

    GLint getUniform(const char* name) const;

    void setMatrixUniform(const char* name, glm::mat4 mat);

};




#endif //TEST_SHADER_H
