//
// Created by Filip on 14.10.2023.
//

#include "Scale.h"

#include <glm/ext/matrix_transform.hpp>

void Scale::action(glm::mat4 &M) {
    M = glm::scale(M, scale);
}

Scale::Scale(const glm::vec3 &scale) : scale(scale) {}
