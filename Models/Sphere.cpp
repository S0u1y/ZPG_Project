//
// Created by Filip on 14.10.2023.
//

#include "Sphere.h"

void Sphere::draw(Shader shader) {
    glBindVertexArray(VAO_A);
    Shape::draw(shader);

    // draw triangles
    glDrawArrays(GL_TRIANGLES, 0, 17280/6); //mode,first,count
}

Sphere::Sphere(float x, float y, float z) : Shape(x, y, z) {
    makeBuffers();
}
