//
// Created by wizzy on 10.10.2023.
//

#ifndef TEST_MODEL_H
#define TEST_MODEL_H

#include "Shape.h"
#include <memory>

class ModelVisitor;

//class which takes an array of vertices and its size to create any kind of models..
class Model : public Shape{
protected:

    const float* vertices;
    size_t size;

    void makeBuffers();

public:
    Model(float x, float y, float z, const float *modelVertices, size_t size);

    void draw() override;

    virtual void accept(ModelVisitor& visitor) = 0;

    //functions required for Visitor..
    GLuint& getVAO(){
        return this->VAO_A;
    }
    GLuint& getVBO(){
        return this->VBO_A;
    }
    void generateVBO(){
        glGenBuffers(1, &VBO_A); // generate the VBO
        glBindBuffer(GL_ARRAY_BUFFER, VBO_A);
        glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), vertices, GL_STATIC_DRAW);
    }

};

#endif //TEST_MODEL_H
