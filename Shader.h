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
    const char* vertex_shader =
            "#version 330\n"
            "layout(location=0) in vec4 vp;"
            "layout(location=1) in vec4 acolor;"
            "out vec4 color;"
            "uniform mat4 MVP;"
            "uniform mat4 viewMatrix;"
            "uniform mat4 projectionMatrix;"
            "void main () {"
            "    gl_Position = projectionMatrix * viewMatrix * MVP * vp;"
            "    color = acolor;"
            "}";

    const char* fragment_shader = "#version 330\n"
                                  "out vec4 frag_colour;"
                                  "in vec4 color;"
                                  "void main () {"
                                  "    frag_colour = color;"
                                  "}";

    GLuint vertexShader{};
    GLuint fragmentShader{};
    GLuint shaderProgram{};

    Camera* camera;

public:
    Shader(Camera* camera) : camera(camera)
    {
    }
    Shader(){};

    void linkCamera(Camera* camera){
        this->camera = camera;
    }

    GLuint create();

    void useShader();

    GLint getUniform(const char* name) const;

    void setMatrixUniform(const char* name, glm::mat4 mat);

};




#endif //TEST_SHADER_H
