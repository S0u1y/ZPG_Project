//
// Created by Filip on 28.10.2023.
//

#ifndef TEST_MATERIAL_H
#define TEST_MATERIAL_H


#include <glm/vec3.hpp>

class Material {
private:
public:
    float r_a{1}, r_d{1}, r_s{1};
    glm::vec3 color{0.385, 0.647, 0.812};

};


#endif //TEST_MATERIAL_H
