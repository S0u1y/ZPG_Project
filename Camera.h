//
// Created by wizzy on 11.10.23.
//

#ifndef TEST_CAMERA_H
#define TEST_CAMERA_H

#include <glm/ext/matrix_float4x4.hpp>



class Shader;
#include <list>
#include "Observer/Subject.h"

class Camera : public Subject{
private:
//    std::list<Shader*> shaders; //observers :)

    glm::vec3 eye{0.f,0.f,3.5f};
    glm::vec3 up{0.f,1.f,0.f};
    glm::vec3 target{0.f,0.f,-0.1f};

    glm::mat4 perspective{1.f};


public:
    Camera(Shader* shader){
        addObserver(shader);
    };
    Camera(){};
    glm::mat4 getCamera();
    void setPerspective(float fov, float ratio, float near, float far);

    const glm::mat4 &getPerspective() const;

    void moveRight(float deltaT);
    void moveLeft(float deltaT);
    void moveBack();
    void moveForward();

    void moveX(float amount);
    void moveY(float amount);
    void moveZ(float amount);

    void lookX(float alpha, float fi);
    void lookX(float amount);
    void lookY(float amount);
};


#endif //TEST_CAMERA_H
