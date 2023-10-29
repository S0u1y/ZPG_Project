//
// Created by wizzy on 11.10.23.
//


#include "Camera.h"

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


void Camera::moveX(float amount) {
    eye.x += amount;
    notify();
}

void Camera::moveY(float amount) {
    eye.y += amount;
    notify();
}

void Camera::moveZ(float amount) {
    eye.z += amount;
    notify();
}

void Camera::lookX(float alpha, float fi) {
    target.x += sin(alpha)*cos(fi);
    notify();
}
//https://open.gl/transformations
void Camera::lookX(float degrees) {
    target = glm::rotate(target, glm::radians(-degrees), up);
    notify();
}

void Camera::lookY(float amount) {
    target = glm::rotate(target, glm::radians(-amount), glm::normalize(glm::cross(target, up)));
    notify();
}

void Camera::moveRight(float deltaT) {
    eye += ( glm::normalize ( glm::cross( target , up ))) * (1.f * deltaT);
    notify();
}

void Camera::moveLeft(float deltaT) {
    eye += -( glm::normalize ( glm::cross( target , up ))) * (1.f * deltaT);
    notify();
}

void Camera::moveBack() {
    eye += -glm::normalize(target) * 0.01f;
    notify();
}

void Camera::moveForward() {
    eye += glm::normalize(target) * 0.1f;
    notify();
}



const glm::mat4 &Camera::getPerspective() const {
    return perspective;
}

const glm::vec3 &Camera::getEye() const {
    return eye;
}

void Camera::setEye(const glm::vec3 &eye) {
    Camera::eye = eye;
}

const glm::vec3 &Camera::getTarget() const {
    return target;
}

void Camera::setTarget(const glm::vec3 &target) {
    Camera::target = target;
}






