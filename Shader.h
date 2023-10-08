//
// Created by wizzy on 27.9.23.
//

#ifndef TEST_SHADER_H
#define TEST_SHADER_H

#include <GL/glew.h>

#include <vector>
#include <cstdio>

#include <string>

using std::vector;

class Shader {
private:
    const char* vertex_shader =
            "#version 330\n"
            "layout(location=0) in vec4 vp;"
            "layout(location=1) in vec4 acolor;"
            "out vec4 color;"
            "uniform mat4 MVP;"
            "void main () {"
            "    gl_Position = MVP * vp;"
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

public:
    Shader(float r, float g, float b)
    {
    }
    Shader(const char* color){
    }

    GLuint create(){
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

    void useShader(){
        glUseProgram(shaderProgram);
    }

    GLint getUniform(const char* name){
        return glGetUniformLocation(shaderProgram, name);
    }

    void setMatrixUniform(const char* name, glm::mat4 &mat){
        useShader();
        glUniformMatrix4fv(getUniform(name), 1, GL_FALSE, &mat[0][0]);
    }

};


#endif //TEST_SHADER_H
