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

class ShaderProgram : public ShaderLoader, public Observer<Camera>, public Observer<Light>{
private:
    Shader vertexShader;
    Shader fragmentShader;
public:
    ShaderProgram(const Shader &vertexShader,
                  const Shader &fragmentShader);

    void onNotify(Camera* camera);
    void onNotify(Light* light);

    void onNotify() override;

    void useShader();

    GLint getUniform(const char* name) const;

    void setUniform(const char* name, glm::mat4 mat);

    void setUniform(const char* name, glm::vec3 vector);

    void setUniform(const char* name, float var);




};


#endif //TEST_SHADERPROGRAM_H
