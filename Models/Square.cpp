//
// Created by wizzy on 14.10.2023.
//

#include "Square.h"


void Square::makeBuffers() {
    glGenVertexArrays(1, &VAO_A);
    glBindVertexArray(VAO_A);

    makeVBO(&VBO_A, a);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(a[0]), nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(a[0]), (GLvoid *)(sizeof(a[0][0])));
    glEnableVertexAttribArray(1);

}

Square::Square(float x, float y, float z) : Shape(x, y, z) {

    a[0][0][0] = - size/2;
    a[0][0][1] = + size/2;
    a[0][0][2] = z;

    a[1][0][0] = size - size/2;
    a[1][0][1] = size/2;
    a[1][0][2] = z;

    a[2][0][0] = - size/2;
    a[2][0][1] = - size + size/2;
    a[2][0][2] = z;

    a[3][0][0] = size - size/2;
    a[3][0][1] = - size + size/2;
    a[3][0][2] = z;

    a[4][0][0] = size - size/2;
    a[4][0][1] = size/2;
    a[4][0][2] = z;

    a[5][0][0] = - size/2;
    a[5][0][1] = - size + size/2;
    a[5][0][2] = z;

    for (auto & i : a) {
        for (int j = 0; j < 4; ++j) {
            i[1][j] = color[j];
        }
    }

    makeBuffers();
    move(glm::vec3(x,y,z));
}

void Square::draw() {

    glBindVertexArray(VAO_A);
    Shape::draw();

    // draw triangles
    glDrawArrays(GL_TRIANGLES, 0, 6); //mode,first,count
}
