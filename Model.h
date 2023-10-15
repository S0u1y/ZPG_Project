//
// Created by Filip on 10.10.2023.
//

#ifndef TEST_MODEL_H
#define TEST_MODEL_H

#include "Shape.h"
#include <memory>


//class which takes an array of vertices and its size to create any kind of models..
class Model : public Shape{
private:
    GLuint VBO_A = 0;
    GLuint VAO_A = 0;

    std::unique_ptr<float> vertices;
    size_t size;

    void makeBuffers();

public:
    Model(float x, float y, float z, const float *modelVertices, size_t size);

    void draw(Shader shader) override;

};

#endif //TEST_MODEL_H
