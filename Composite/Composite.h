//
// Created by wizzy on 08.10.2023.
//
//

#ifndef TEST_COMPOSITE_H
#define TEST_COMPOSITE_H

#include "../Shader.h"


class Composite{
public:
    virtual void Add(Composite* composite) = 0;
    virtual void Remove(Composite* composite) = 0;

    virtual void action(glm::mat4 &M) = 0;

//    Composite* parent;
};

#endif //TEST_COMPOSITE_H
