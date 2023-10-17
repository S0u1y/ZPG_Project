//
// Created by Filip on 14.10.2023.
//

#include "Triangle.h"


void Triangle::makeBuffers() {
    glGenVertexArrays(1, &VAO_A);
    glBindVertexArray(VAO_A);

    makeVBO(&VBO_A, a);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(a[0]), nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(a[0]), (GLvoid *)(sizeof(a[0][0])));
    glEnableVertexAttribArray(1);

}

Triangle::Triangle(float x, float y, float z) : Shape(x, y, z) {
//        a[0][0][0] = x;
//        a[0][0][1] = y;
//        a[0][0][2] = z;
//
//        a[1][0][0] = x+size;
//        a[1][0][1] = y;
//        a[1][0][2] = z;
//
//        a[2][0][0] = x;
//        a[2][0][1] = y-size;
//        a[2][0][2] = z;

    a[0][0][0] = - size/4;
    a[0][0][1] = + size/4;
    a[0][0][2] = z;

    a[1][0][0] =size- size/4;
    a[1][0][1] =size/4;
    a[1][0][2] = z;

    a[2][0][0] =- size/4;
    a[2][0][1] =-size + size/4;
    a[2][0][2] = z;

    for (auto & i : a) {
        for (int j = 0; j < 4; ++j) {
            i[1][j] = color[j];
        }
    }

    makeBuffers();
//        move(x,y,z);
}

void Triangle::draw() {

    glBindVertexArray(VAO_A);
    Shape::draw();
    // draw triangles
    glDrawArrays(GL_TRIANGLES, 0, 3); //mode,first,count
}
