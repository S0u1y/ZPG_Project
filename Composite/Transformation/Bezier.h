//
// Created by Filip on 12.12.2023.
//

#ifndef TEST_BEZIER_H
#define TEST_BEZIER_H

#include "Transformation.h"

class Bezier : public Composite{
private:
    glm::mat4x3 points;
    float t;
    glm::mat4 coefficients = glm::mat4(glm::vec4(-1.0, 3.0, -3.0, 1.0),
                                       glm::vec4(3.0, -6.0, 3.0, 0),
                                       glm::vec4(-3.0, 3.0, 0, 0),
                                       glm::vec4(1.0, 0, 0, 0));


    void Add(Composite *composite) override;

    void Remove(Composite *composite) override;
public:
    void action(glm::mat4 &p_M) override;

    Bezier(const glm::mat4x3 &points, float t);
};


#endif //TEST_BEZIER_H
