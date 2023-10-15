//
// Created by Filip on 14.10.2023.
//

#ifndef TEST_MOVE_H
#define TEST_MOVE_H

#include "../Composite.h"
#include <glm/ext/matrix_transform.hpp>

class Move : public Composite{
private:
    glm::vec3 vector;


    void Add(Composite *composite) override {}
    void Remove(Composite *composite) override {}

public:
    Move(const glm::vec3 &vector) : vector(vector) {}

    void action(glm::mat4 &M) override {
        M = glm::translate(M, vector);
    }
};


#endif //TEST_MOVE_H
