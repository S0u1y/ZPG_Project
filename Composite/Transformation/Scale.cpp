//
// Created by wizzy on 14.10.2023.
//

#include "Scale.h"

#include <glm/ext/matrix_transform.hpp>

void Scale::action(glm::mat4 &M) {
//    M = glm::scale(M, scale);
    M *= this->M;
}

Scale::Scale(const glm::vec3 &scale) : scale(scale) {
    M = glm::scale(M, scale);
}
