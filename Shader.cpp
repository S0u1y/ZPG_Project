//
// Created by wizzy on 11.10.23.
//
#include <cstring>
#include "Shader.h"
#include "Camera.h"
#include "Light.h"

GLuint Shader::create() {
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertex_shader, NULL);
    glCompileShader(vertexShader);

    GLint status;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
    if(status == GL_FALSE){
        GLint logSize;
        glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &logSize);
        GLchar* errorLog = new GLchar[logSize+1];
        glGetShaderInfoLog(vertexShader, logSize, NULL, errorLog);
        printf("Compile failed: %s \n", errorLog);
        delete [] errorLog;
    }

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragment_shader, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
    if(status == GL_FALSE){
        GLint logSize;
        glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &logSize);
        GLchar* errorLog = new GLchar[logSize+1];
        glGetShaderInfoLog(fragmentShader, logSize, NULL, errorLog);
        printf("Compile failed: %s \n", errorLog);
        delete [] errorLog;
    }

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, fragmentShader);
    glAttachShader(shaderProgram, vertexShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv ( shaderProgram , GL_LINK_STATUS , & status );
    if ( status == GL_FALSE )
    {
        GLint info ;
        glGetProgramiv ( shaderProgram , GL_INFO_LOG_LENGTH ,& info );
        GLint infoLogLength;
        GLchar * strInfoLog = new GLchar [ infoLogLength + 1];
        glGetProgramInfoLog ( shaderProgram , info , NULL , strInfoLog );
        fprintf ( stderr , "Linker failure : %s \n" , strInfoLog );
        delete [] strInfoLog ;
    }

    return shaderProgram;
}

void Shader::useShader() {
    glUseProgram(shaderProgram);
}

GLint Shader::getUniform(const char *name) const {
    return glGetUniformLocation(shaderProgram, name);
}

void Shader::setMatrixUniform(const char *name, glm::mat4 mat) {
    useShader();
    auto id = getUniform(name);
    if(id < 0)
        return;
    glUniformMatrix4fv(id, 1, GL_FALSE, &mat[0][0]);
}

void Shader::setUniformVec3(const char *name, glm::vec3 vector) {
    useShader();
    auto id = getUniform(name);
    if(id < 0)
        return;

    glUniform3f(id, vector.x, vector.y, vector.z);
}

//pass camera through function instead?
void Shader::onNotify(Camera* subject) {
    useShader();
    setMatrixUniform("projectionMatrix", subject->getPerspective());
    setMatrixUniform("viewMatrix", subject->getCamera());
    setUniformVec3("cameraPosition", subject->getEye());
}

void Shader::onNotify(Light *light) {

}

void Shader::onNotify() {
}




