//
// Created by wizzy on 14.10.2023.
//

#include "Move.h"

void Move::action(glm::mat4 &M) {
    M = glm::translate(M, vector);
}
