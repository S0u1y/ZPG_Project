//
// Created by wizzy on 14.10.2023.
//

#include "Shape.h"

#include "../Shaders/ShaderProgram.h"

#include "../Composite/Transformation/Rotation.h"
#include "../Composite/Transformation/Move.h"
#include "../Composite/Transformation/Scale.h"

void Shape::draw() {
    transformation.action(*shader);
    shader->setUniform("objectColor", material.color);
}

void Shape::rotate(float angle, glm::vec3 axis) {
    transformation.Add(new Rotation(angle, axis));
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

void Shape::setShader(ShaderProgram *shader) {
    this->shader = shader;
}
