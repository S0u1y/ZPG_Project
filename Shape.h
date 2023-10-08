//
// Created by wizzy on 27.9.23.
//

#ifndef TEST_SHAPE_H
#define TEST_SHAPE_H


#include "Composite/Composite.h"

class Shape {
protected:
    float x,y,z;
    float size = 0.5;

    Transformation transformation;

    Shape(float x, float y, float z) : x(x), y(y), z(z) {};
    Shape(float x, float y, float z, float size) : x(x), y(y), z(z), size(size) {};



    template<typename T>
    void makeVBO(GLuint* VBO, T& points){
        glGenBuffers(1, VBO); // generate the VBO
        glBindBuffer(GL_ARRAY_BUFFER, *VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof (points), points, GL_STATIC_DRAW);
    }

    //unsure about this function.. might delete in the future
    void makeVAO(GLuint& VAO){
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, VAO);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    }
public:
    virtual void draw(Shader shader) {
        transformation.action(shader);
    };

    void rotate(float angle, glm::vec3 axis){
        transformation.Add(new Rotation(angle, axis));
    }
};



#endif //TEST_SHAPE_H
