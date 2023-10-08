//
// Created by Filip on 27.09.2023.
//

#ifndef PRVNICLION_SQUARE_H
#define PRVNICLION_SQUARE_H


#include "Shape.h"

class Square : public Shape {
private:
    GLuint VBO_A = 0;
    GLuint VAO_A = 0;

public:

    float color[4] = {1,1,1,1};

    float a[6][2][4]={
            {
                { -.5f , -.5f , .5f , 1 } ,
                { 1 , 1 , 0 , 1 } } ,
            {
                { -.5f , .5f , .5f , 1 } ,
                { 1 , 0 , 0 , 1 } } ,
            {
                { .5f , .5f , .5f , 1 } ,
                { 0 , 0 , 0 , 1 } },
            {
                    { -.5f , -.5f , .5f , 1 } ,
                    { 1 , 1 , 0 , 1 } } ,
            {
                    { -.5f , .5f , .5f , 1 } ,
                    { 1 , 0 , 0 , 1 } } ,
            {
                    { .5f , .5f , .5f , 1 } ,
                    { 0 , 0 , 0 , 1 } }
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

    Square(float x, float y, float z) : Shape(x, y, z) {

        a[0][0][0] = x;
        a[0][0][1] = y;
        a[0][0][2] = z;

        a[1][0][0] = x+size;
        a[1][0][1] = y;
        a[1][0][2] = z;

        a[2][0][0] = x;
        a[2][0][1] = y-size;
        a[2][0][2] = z;

        a[3][0][0] = x+size;
        a[3][0][1] = y-size;
        a[3][0][2] = z;

        a[4][0][0] = x+size;
        a[4][0][1] = y;
        a[4][0][2] = z;

        a[5][0][0] = x;
        a[5][0][1] = y-size;
        a[5][0][2] = z;

        for (auto & i : a) {
            for (int j = 0; j < 4; ++j) {
                i[1][j] = color[j];
            }
        }

        makeBuffers();
    }

    void draw(Shader shader) override{

        shader.useShader();

        glBindVertexArray(VAO_A);
        shader.setMatrixUniform("MVP", transformation.M);

        // draw triangles
        glDrawArrays(GL_TRIANGLES, 0, 6); //mode,first,count
    }

};


#endif //PRVNICLION_SQUARE_H
