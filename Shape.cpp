//
// Created by Filip on 14.10.2023.
//

#include "Shape.h"

glm::vec3 Shape::getPosition() {
    return glm::vec3(x,y,z);
}

void Shape::draw(Shader shader) {
    transformation.action(shader);
}

void Shape::rotate(float angle, glm::vec3 axis) {
    glm::vec3 old_position = glm::vec3(this->x, this->y, this->z);
    transformation.Add(new Rotation(angle, axis));
//        move(glm::vec3(this->size/4, -this->size/4, 0));
}

void Shape::move(glm::vec3 vector) {
    transformation.Add(new Move(vector));
}

void Shape::move(float x, float y, float z) {
    move(glm::vec3 (x,y,z));
}

void Shape::scale(glm::vec3 scale) {
    transformation.Add(new Scale{scale});
}
