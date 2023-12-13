//
// Created by Filip on 12.12.2023.
//

#include "Bezier.h"
#include "glm/ext/matrix_transform.hpp"

void Bezier::action(glm::mat4 &p_M) {
    glm::vec4 parameters = glm::vec4(pow(t, 3),
                                     pow(t, 2),
                                     t,
                                     1.0);
    glm::vec3 point = parameters * coefficients * glm::transpose(points);
    p_M = glm::translate(p_M, point);
}

void Bezier::Add(Composite *composite) {}

void Bezier::Remove(Composite *composite) {}

Bezier::Bezier(const glm::mat4x3 &points, float t) : points(points), t(t) {}
