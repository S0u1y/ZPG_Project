//
// Created by wizzy on 11.10.23.
//


#include "Camera.h"
#include "Shader.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>

glm::mat4 Camera::getCamera() {
    return glm::lookAt(eye, eye+target, up);
}

void Camera::setPerspective(float fov, float ratio, float near, float far) {
    perspective = glm::perspective(fov, ratio, near, far);
}

void Camera::metoda() {
    shader->useShader();
    shader->setMatrixUniform("viewMatrix", perspective);
    shader->setMatrixUniform("projectionMatrix", getCamera());
}

