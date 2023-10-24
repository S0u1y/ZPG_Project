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
#include "Observer/Observer.h"

using std::vector;

class Camera;

class Shader : public Observer<Camera>{
private:
    const char* vertex_shader;

    const char* fragment_shader;

    GLuint vertexShader{};
    GLuint fragmentShader{};
    GLuint shaderProgram{};

public:
    Shader(){};

    Shader(const char* vertexShader, const char* fragmentShader)
    : vertex_shader(vertexShader), fragment_shader(fragmentShader)
    {}

    void onNotify() override;

    GLuint create();

    void useShader();

    GLint getUniform(const char* name) const;

    void setMatrixUniform(const char* name, glm::mat4 mat);

    void setUniformFloat(const char* name, float var){
        useShader();
        glUniform1f(getUniform(name), var);
    }

    void setUniformVec3(const char* name, glm::vec3 vector){
        useShader();
        glUniform3f(getUniform(name), vector.x, vector.y, vector.z);
    }

};




#endif //TEST_SHADER_H
