//
// Created by wizzy on 25.10.23.
//

#ifndef TEST_SHADERPROGRAM_H
#define TEST_SHADERPROGRAM_H


#include <glm/vec3.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include "ShaderLoader.h"
#include "Shader.h"
#include "../Observer/Observer.h"


class Camera; class Light;

using glm::vec3;
struct lightSource{
    vec3 lightPosition;
    vec3 lightDirection;
    vec3 lightColor;
    float angle;
    float linear;
    float quadratic;
    float constant;
};

class ShaderProgram : public ShaderLoader, public Observer<Camera>, public Observer<Light>{
private:
    Shader vertexShader;
    Shader fragmentShader;
public:
    ShaderProgram(const Shader &vertexShader,
                  const Shader &fragmentShader);

    ShaderProgram(const char* vertexShaderFilepath, const char* fragmentShaderFilepath);

    void onNotify(Camera* camera);
    void onNotify(Light* light);

    void onNotify() override;

    void useShader();
    void unbindShader(){
        glUseProgram(0);
    }

    GLint getUniform(const char* name) const;

    void setUniform(const char* name, glm::mat4 mat);

    void setUniform(const char* name, glm::vec3 vector);

    void setUniform(const char* name, float var);

    void setUniform(const char* name, int var);

    void setUniform(std::string name, lightSource lightSource);




};


#endif //TEST_SHADERPROGRAM_H
