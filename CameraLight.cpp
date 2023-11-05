//
// Created by Filip on 05.11.2023.
//

#include "CameraLight.h"
#include "Camera.h"

void CameraLight::onNotify(Camera *subject) {

    this->position = subject->getEye() + subject->getTarget();
    this->direction = subject->getTarget();
    notify();
}

void CameraLight::onNotify() {}

CameraLight::CameraLight(const glm::vec3 &position, const glm::vec3 &direction, float angle)
: Light(position,direction,angle)
{
    this->a = 0;
    this->b = 0;
    this->k = 1;
}

CameraLight::CameraLight(Camera *camera, float angle)
: Light(camera->getEye(), camera->getTarget(), angle)
{
    camera->addObserver(this);
}
