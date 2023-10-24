//
// Created by wizzy on 14.10.2023.
//

#ifndef TEST_SCALE_H
#define TEST_SCALE_H

#include "../Composite.h"

class Scale : public Composite{
private:
    glm::vec3 scale;

    void Add(Composite *composite) override{};

    void Remove(Composite *composite) override{};

public:
    Scale(const glm::vec3 &scale);

    void action(glm::mat4 &M) override;
};


#endif //TEST_SCALE_H
