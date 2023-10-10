//
// Created by Filip on 08.10.2023.
//

#ifndef TEST_TRIANGLE_H
#define TEST_TRIANGLE_H

#include "Shape.h"
#include "Shader.h"

class Triangle : public Shape{
private:
    GLuint VBO_A = 0;
    GLuint VAO_A = 0;

    float color[4] = {1,1,1,1};

    float a[3][2][4]={
            {
                    { -.5f , -.5f , .5f , 1 } ,
                    { 1 , 1 , 0 , 1 } } ,
            {
                    { -.5f , .5f , .5f , 1 } ,
                    { 1 , 0 , 0 , 1 } } ,
            {
                    { .5f , .5f , .5f , 1 } ,
                    { 0 , 0 , 0 , 1 } },
    };

    void makeBuffers(){
        glGenVertexArrays(1, &VAO_A);
        glBindVertexArray(VAO_A);

        makeVBO(&VBO_A, a);

        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(a[0]), nullptr);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(a[0]), (GLvoid *)(sizeof(a[0][0])));
        glEnableVertexAttribArray(1);

    }

public:

    Triangle(float x, float y, float z) : Shape(x, y, z) {
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
        move(x,y,z);
    }

    void draw(Shader shader) override {

        glBindVertexArray(VAO_A);
        Shape::draw(shader);
        // draw triangles
        glDrawArrays(GL_TRIANGLES, 0, 3); //mode,first,count
    }
};

#endif //TEST_TRIANGLE_H
