//
// Created by Filip on 07.11.2023.
//

#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(const glm::vec3 &position, const glm::vec3 &direction, float angle)
: Light(position,direction,angle)
{
    type = 2;
}
