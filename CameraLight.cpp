//
// Created by Filip on 05.11.2023.
//

#include "CameraLight.h"
#include "Camera.h"

void CameraLight::onNotify(Camera *subject) {

    this->position = subject->getEye();
    this->direction = subject->getTarget();
    notify();
}

void CameraLight::onNotify() {}

CameraLight::CameraLight(const glm::vec3 &position, const glm::vec3 &direction, float angle)
: Light(position,direction,angle)
{
    this->linear = 0;
    this->constant = 0;
    this->quadratic = 1;
}

CameraLight::CameraLight(Camera *camera, float angle)
: Light(camera->getEye(), camera->getTarget(), angle)
{
    camera->addObserver(this);
}
