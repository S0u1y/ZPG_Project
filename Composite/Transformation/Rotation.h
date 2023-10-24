//
// Created by wizzy on 14.10.2023.
//

#ifndef TEST_ROTATION_H
#define TEST_ROTATION_H


#include "../Composite.h"

#include <glm/ext/matrix_transform.hpp>

class Rotation : public Composite{
private:
    float angle;
    glm::vec3 axis;


    void Add(Composite *composite) override {
    }
    void Remove(Composite *composite) override {
    }

public:
    Rotation(float angle, const glm::vec3 &axis) : angle(angle), axis(axis) {}

    void action(glm::mat4 &M) override;

};


#endif //TEST_ROTATION_H
