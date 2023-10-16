//
// Created by wizzy on 11.10.23.
//


#include "Camera.h"

#include "Shader.h"

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtx/rotate_vector.hpp>


glm::mat4 Camera::getCamera() {
    glm::mat4 view{1.f};
    view = glm::lookAt(eye, eye+target, up);
    return view;
}

void Camera::setPerspective(float fov, float ratio, float near, float far) {
    glm::mat4 projection{1.f};
    projection = glm::perspective(glm::radians(fov), ratio, near, far);//glm::radians
    perspective = projection;
}

void Camera::metoda() {
    setPerspective(60.f, (float)4/3, 0.1f, 100.f);

    for (const auto &item: shaders){
        item->useShader();
        item->setMatrixUniform("projectionMatrix", perspective);
        item->setMatrixUniform("viewMatrix", getCamera());
    }



}

void Camera::moveX(float amount) {
    eye.x += amount;
}

void Camera::moveY(float amount) {
    eye.y += amount;
}

void Camera::moveZ(float amount) {
    eye.z += amount;
}

void Camera::lookX(float alpha, float fi) {
    target.x += sin(alpha)*cos(fi);
}

void Camera::lookX(float degrees) {
    target = glm::rotate(target, glm::radians(-degrees), up);

}

void Camera::moveRight(float deltaT) {
    eye += ( glm::normalize ( glm::cross( target , up ))) * (1.f * deltaT);
}

void Camera::moveLeft(float deltaT) {
    eye += -( glm::normalize ( glm::cross( target , up ))) * (1.f * deltaT);
}

void Camera::moveBack() {
    eye += -glm::normalize(target) * 0.01f;
}

void Camera::moveForward() {
    eye += glm::normalize(target) * 0.01f;
}


