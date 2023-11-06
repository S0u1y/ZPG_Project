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

void ShaderProgram::setUniform(const char *name, float floating_number) {
    useShader();
    auto id = getUniform(name);
    if(id < 0)
        return;
    glUniform1f(getUniform(name), floating_number);
}

void ShaderProgram::setUniform(const char *name, int integer) {
    useShader();
    auto id = getUniform(name);
    if(id < 0)
        return;
    glUniform1i(getUniform(name), integer);
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

    lightSource light_{
        light->getPosition(),
        light->getDirection(),
        light->getLightColor(),
        light->getAngle(),
        light->linear,
        light->quadratic,
        light->constant
    };
    setUniform("lightSources["+std::to_string(light->id)+"]", light_);
}

void ShaderProgram::onNotify() {
}

void ShaderProgram::setUniform(std::string name, lightSource lightSource) {
    if(getUniform((name + ".lightPosition").c_str()) < 0){
//        printf("%s", ("Shader has no " + name + ".lightPosition\n").c_str());
        return;
    }
    setUniform((name + ".lightPosition").c_str(), lightSource.lightPosition);
    setUniform((name + ".lightVector").c_str(), lightSource.lightDirection);
    setUniform((name + ".lightAngle").c_str(), lightSource.angle);
    setUniform((name + ".lightColor").c_str(), lightSource.lightColor);
    setUniform((name + ".linear").c_str(), lightSource.linear);
    setUniform((name + ".quadratic").c_str(), lightSource.quadratic);
    setUniform((name + ".constant").c_str(), lightSource.constant);
}







