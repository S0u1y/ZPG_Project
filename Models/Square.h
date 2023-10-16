//
// Created by Filip on 27.09.2023.
//

#ifndef PRVNICLION_SQUARE_H
#define PRVNICLION_SQUARE_H


#include "Shape.h"

class Square : public Shape {
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


    void makeBuffers();

    Square(float x, float y, float z);

    void draw(Shader shader) override;

};


#endif //PRVNICLION_SQUARE_H
