//
// Created by wizzy on 11.10.23.
//
#include "Shader.h"
#include "Camera.h"

GLuint Shader::create() {
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertex_shader, NULL);
    glCompileShader(vertexShader);
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragment_shader, NULL);
    glCompileShader(fragmentShader);
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, fragmentShader);
    glAttachShader(shaderProgram, vertexShader);
    glLinkProgram(shaderProgram);

    GLint status ;
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
    glUniformMatrix4fv(getUniform(name), 1, GL_FALSE, &mat[0][0]);
}

//pass camera through function instead?
void Shader::onNotify() {
    useShader();
    setMatrixUniform("projectionMatrix", camera->getPerspective());
    setMatrixUniform("viewMatrix", camera->getCamera());
}
