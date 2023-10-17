//
// Created by wizzy on 11.10.23.
//


#include "Camera.h"

#include "Shader.h"

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtx/rotate_vector.hpp>

void Camera::linkShader(Shader *shader) {
    shaders.push_back(shader);
}

void Camera::notifyShaders() {//notify all observers :)
    for (const auto &item: shaders){
        item->onNotify();
    }
}

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


void Camera::moveX(float amount) {
    eye.x += amount;
    notifyShaders();
}

void Camera::moveY(float amount) {
    eye.y += amount;
    notifyShaders();
}

void Camera::moveZ(float amount) {
    eye.z += amount;
    notifyShaders();
}

void Camera::lookX(float alpha, float fi) {
    target.x += sin(alpha)*cos(fi);
    notifyShaders();
}

void Camera::lookX(float degrees) {
    target = glm::rotate(target, glm::radians(-degrees), up);
    notifyShaders();
}

void Camera::lookY(float amount) {
    target = glm::rotate(target, glm::radians(-amount), glm::normalize(glm::cross(target, up)));
    notifyShaders();
}

void Camera::moveRight(float deltaT) {
    eye += ( glm::normalize ( glm::cross( target , up ))) * (1.f * deltaT);
    notifyShaders();
}

void Camera::moveLeft(float deltaT) {
    eye += -( glm::normalize ( glm::cross( target , up ))) * (1.f * deltaT);
    notifyShaders();
}

void Camera::moveBack() {
    eye += -glm::normalize(target) * 0.01f;
    notifyShaders();
}

void Camera::moveForward() {
    eye += glm::normalize(target) * 0.01f;
    notifyShaders();
}



const glm::mat4 &Camera::getPerspective() const {
    return perspective;
}






