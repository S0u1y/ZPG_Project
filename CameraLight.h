//
// Created by Filip on 05.11.2023.
//

#ifndef TEST_CAMERALIGHT_H
#define TEST_CAMERALIGHT_H

#include "Light.h"
#include "Observer/Observer.h"
#include "Observer/Subject.h"

class Camera;

class CameraLight : public Light, public Observer<Camera>{
public:
    CameraLight(const glm::vec3 &position, const glm::vec3 &direction, float angle);
    CameraLight(Camera* camera, float angle);

    void onNotify(Camera *subject) override;

    void onNotify() override;
};


#endif //TEST_CAMERALIGHT_H
