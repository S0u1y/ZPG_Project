//
// Created by Filip on 10.10.2023.
//

#ifndef TEST_MODEL_H
#define TEST_MODEL_H

#include "Shape.h"
#include <memory>

class Model : public Shape{
private:
    GLuint VBO_A = 0;
    GLuint VAO_A = 0;

    std::unique_ptr<float> vertices;
    size_t size;

    void makeBuffers(){
        glGenVertexArrays(1, &VAO_A);
        glBindVertexArray(VAO_A);

        glGenBuffers(1, &VBO_A); // generate the VBO
        glBindBuffer(GL_ARRAY_BUFFER, VBO_A);
        glBufferData(GL_ARRAY_BUFFER, size*sizeof(float), vertices.get(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*6, nullptr);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float)*6, (GLvoid *)(sizeof(float)*3));
        glEnableVertexAttribArray(1);

    }

public:
    Model(float x, float y, float z, const float *modelVertices, size_t size) : Shape(x, y, z), size(size) {
        vertices = std::unique_ptr<float>((float*)malloc(size*sizeof(float)));
        for (int i = 0; i < size; ++i) {
            (vertices.get())[i] = modelVertices[i];
        }
        makeBuffers();
    }

    void draw(Shader shader) override {

        glBindVertexArray(VAO_A);
        Shape::draw(shader);
        // draw triangles
        glDrawArrays(GL_TRIANGLES, 0, size/6); //mode,first,count
    }

};

#endif //TEST_MODEL_H
