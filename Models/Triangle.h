//
// Created by Filip on 08.10.2023.
//

#ifndef TEST_TRIANGLE_H
#define TEST_TRIANGLE_H

#include "Shape.h"
#include "../Shader.h"

class Triangle : public Shape{
private:

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

    void makeBuffers();

public:

    Triangle(float x, float y, float z);

    void draw() override;
};

#endif //TEST_TRIANGLE_H
