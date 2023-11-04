//
// Created by wizzy on 25.10.23.
//

#include <glm/trigonometric.hpp>
#include "ShaderProgram.h"

#include "../Camera.h"
#include "../Light.h"

ShaderProgram::ShaderProgram(const Shader &vertexShader, const Shader &fragmentShader)
: ShaderLoader(vertexShader.filepath, fragmentShader.filepath, &this->shaderProgramID)
{}
ShaderProgram::ShaderProgram(const char *vertexShaderFilepath, const char *fragmentShaderFilepath)
: ShaderLoader(vertexShaderFilepath, fragmentShaderFilepath, &this->shaderProgramID)
{}

void ShaderProgram::setUniform(const char *name, float var) {
    useShader();
    glUniform1f(getUniform(name), var);
}

void ShaderProgram::useShader() {
    glUseProgram(shaderProgramID);
}

GLint ShaderProgram::getUniform(const char *name) const {
    return glGetUniformLocation(shaderProgramID, name);
}

void ShaderProgram::setUniform(const char *name, glm::mat4 mat) {
    useShader();
    auto id = getUniform(name);
    if(id < 0)
        return;
    glUniformMatrix4fv(id, 1, GL_FALSE, &mat[0][0]);
}

void ShaderProgram::setUniform(const char *name, glm::vec3 vector) {
    useShader();
    auto id = getUniform(name);
    if(id < 0)
        return;

    glUniform3f(id, vector.x, vector.y, vector.z);
}

void ShaderProgram::onNotify(Camera* subject) {
    useShader();
    setUniform("projectionMatrix", subject->getPerspective());
    setUniform("viewMatrix", subject->getCamera());
    setUniform("cameraPosition", subject->getEye());
}

void ShaderProgram::onNotify(Light *light) {
    useShader();
    setUniform("lightPosition", light->getPosition());
    setUniform("lightVector", light->getDirection());
    setUniform("lightAngle", light->getAngle());
    setUniform("lightColor", light->getLightColor());
    setUniform("a", light->a);
    setUniform("b", light->b);
    setUniform("k", light->k);
}

void ShaderProgram::onNotify() {
}





