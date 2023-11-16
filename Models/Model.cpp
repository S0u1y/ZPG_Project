//
// Created by wizzy on 14.10.2023.
//

#include "Model.h"


void Model::makeBuffers() {
    glGenVertexArrays(1, &VAO_A);
    glBindVertexArray(VAO_A);

    generateVBO();

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*6, nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float)*6, (GLvoid *)(sizeof(float)*3));
    glEnableVertexAttribArray(1);

}

Model::Model(float x, float y, float z, const float *modelVertices, size_t size) : Shape(x, y, z), size(size) {
//    vertices = std::unique_ptr<float>((float*)malloc(size*sizeof(float)));
//    for (int i = 0; i < size; ++i) {
//        (vertices.get())[i] = modelVertices[i];
//    }

    vertices = new float[size];
    for (int i = 0; i < size; ++i) {
        vertices[i] = modelVertices[i];
    }

//    makeBuffers();
    move(x,y,z);
}

Model::Model(float x1, float y1, float z1, float x, float y, float z, std::vector<float> modelVertices,
             size_t size) : Shape(x1, y1, z1) {
    vertices = new float[size];
    for (int i = 0; i < size; ++i) {
        vertices[i] = modelVertices[i];
    }

    move(x, y, z);
}

void Model::draw() {

    glBindVertexArray(VAO_A);
    Shape::draw();

}



