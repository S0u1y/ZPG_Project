//
// Created by wizzy on 14.10.2023.
//

#include "Rotation.h"

void Rotation::action(glm::mat4 &M) {
//    M = glm::rotate(M, angle, axis);
    M *= this->M;
}
