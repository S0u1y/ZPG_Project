//
// Created by wizzy on 14.10.2023.
//

#include "Rotation.h"

void Rotation::action(glm::mat4 &p_M) {
//    M = glm::rotate(M, angle, axis);
    p_M *= this->M;
}
