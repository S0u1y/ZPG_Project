//
// Created by wizzy on 27.9.23.
//

#ifndef TEST_SHAPE_H
#define TEST_SHAPE_H

class Composite;
class ShaderProgram;
#include "../Composite/Transformation/Transformation.h"
#include "../Material.h"

#include <GL/glew.h>


class Shape {
protected:


    GLuint VBO_A = 0;
    GLuint VAO_A = 0;

    ShaderProgram* shader;

    Shape(float x, float y, float z){};
    Shape(float x, float y, float z, float size): size(size) {};

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
    Transformation transformation;
    Material material;

    float size = 0.5;

    void setShader(ShaderProgram* shader);

    virtual void draw() = 0;

    virtual void rotate(float angle, glm::vec3 axis);

    virtual void move(glm::vec3 vector);
    virtual void move(float x, float y, float z);
    virtual void scale(glm::vec3 scale);
    void addTransform(Composite* component){
        transformation.Add(component);
    }
    void copyTransform(Transformation* other){
        other = &transformation;
    }
    void performTransformation(){
        transformation.action(*shader);
    }
};



#endif //TEST_SHAPE_H
