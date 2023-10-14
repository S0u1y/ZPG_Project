//
// Created by wizzy on 11.10.23.
//

#ifndef TEST_CAMERA_H
#define TEST_CAMERA_H

#include <glm/ext/matrix_float4x4.hpp>

class Shader;

class Camera{
private:
    Shader *shader;
    glm::vec3 eye{0,0,0.0};
    glm::vec3 up{0,1,0};
    glm::vec3 target{0,0,1};

    glm::mat4 perspective;

public:
    Camera(Shader* shader): shader(shader){};
    glm::mat4 getCamera();
    void setPerspective(float fov, float ratio, float near, float far);
    void metoda();

};


#endif //TEST_CAMERA_H
