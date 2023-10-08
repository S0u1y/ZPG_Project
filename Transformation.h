//
// Created by Filip on 08.10.2023.
//

#ifndef TEST_TRANSFORMATION_H
#define TEST_TRANSFORMATION_H

#include <glm/gtc/matrix_transform.hpp>


class Transformation {
private:

public:
    glm::mat4 M = glm::mat4(1.0f);

    //rotates matrice by angle along the vector axis (keep normalized)
    void rotate(float angle, glm::vec3 vector){
        M = glm::rotate(M, angle, vector);
    }
};


#endif //TEST_TRANSFORMATION_H
