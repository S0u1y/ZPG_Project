//
// Created by Filip on 25.10.2023.
//

#ifndef TEST_LIGHT_H
#define TEST_LIGHT_H


#include <glm/vec3.hpp>

#include "Observer/Subject.h"

class Light : public Subject<Light>{
private:
    glm::vec3 position{};
    glm::vec3 direction{}; //direction in which the light shines
    float angle{}; //angle (cone) of light

    glm::vec3 lightColor{1,1,1};

public:
    float a{0.01}, b{0.01};

    Light()= default;
    Light(const glm::vec3 &position, const glm::vec3 &direction, float angle) : position(position),
                                                                                direction(direction), angle(angle) {}

    void move(glm::vec3 vector){
        position += vector;
        notify();
    }

    const glm::vec3 &getPosition() const {
        return position;
    }

    const glm::vec3 &getDirection() const {
        return direction;
    }

    void setDirection(const glm::vec3 &direction) {
        Light::direction = direction;
        notify();
    }

    float getAngle() const {
        return angle;
    }

    void setAngle(float angle) {
        Light::angle = angle;
        notify();
    }

    const glm::vec3 &getLightColor() const {
        return lightColor;
    }

    void setLightColor(const glm::vec3 &lightColor) {
        Light::lightColor = lightColor;
        notify();
    }

};


#endif //TEST_LIGHT_H
