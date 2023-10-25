//
// Created by Filip on 25.10.2023.
//

#ifndef TEST_LIGHT_H
#define TEST_LIGHT_H


#include <glm/vec3.hpp>

#include "Observer/Subject.h"

class Light : public Subject<Light>{
public:
    glm::vec3 position;

    void move(glm::vec3 vector){
        position += vector;
        notify();
    }
};


#endif //TEST_LIGHT_H
