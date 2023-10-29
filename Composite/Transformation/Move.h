//
// Created by wizzy on 14.10.2023.
//

#ifndef TEST_MOVE_H
#define TEST_MOVE_H

#include "../Composite.h"
#include <glm/ext/matrix_transform.hpp>

class Move : public Composite{
private:
    glm::vec3 vector;
    glm::mat4 M{1.f};

    void Add(Composite *composite) override {}
    void Remove(Composite *composite) override {}

public:
    Move(const glm::vec3 &vector) : vector(vector) {
        M = glm::translate(M, vector);
    }

    void action(glm::mat4 &M) override;
};


#endif //TEST_MOVE_H
