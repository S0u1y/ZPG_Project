//
// Created by wizzy on 11.10.23.
//

#ifndef TEST_CAMERA_H
#define TEST_CAMERA_H

#include <glm/ext/matrix_float4x4.hpp>



class Shader;
#include <list>

class Camera{
private:
    Shader *shader;
    glm::vec3 eye{0.f,0.f,1.78f};
    glm::vec3 up{0.f,1.f,0.f};
    glm::vec3 target{0.f,0.f,-0.1f};

    glm::mat4 perspective{1.f};
    std::list<Shader*> shaders;

public:
    Camera(Shader* shader){
        shaders.push_back(shader);
    };
    Camera(){};
    void linkShader(Shader* shader){
        shaders.push_back(shader);
    }
    glm::mat4 getCamera();
    void setPerspective(float fov, float ratio, float near, float far);
    void metoda();

    void moveRight(float deltaT);
    void moveLeft(float deltaT);
    void moveBack();
    void moveForward();

    void moveX(float amount);
    void moveY(float amount);
    void moveZ(float amount);

    void lookX(float alpha, float fi);
    void lookX(float amount);

};


#endif //TEST_CAMERA_H
