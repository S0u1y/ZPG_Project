//
// Created by Filip on 29.10.2023.
//

#ifndef TEST_KILLMEPLEASE_H
#define TEST_KILLMEPLEASE_H


#include "Composite.h"
#include "Transformation/Transformation.h"
#include "../Models/Shape.h"

class killmeplease : public Transformation{
public:
    std::vector<Shape*> shapes;

    void action();

private:
    void action(glm::mat4 &M) override;

public:
    void Add(Composite *composite) override;

    void Remove(Composite *composite) override;
};


#endif //TEST_KILLMEPLEASE_H
