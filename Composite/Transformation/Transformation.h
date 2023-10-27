//
// Created by wizzy on 14.10.2023.
//

#ifndef TEST_TRANSFORMATION_H
#define TEST_TRANSFORMATION_H

#include <vector>

#include "../Composite.h"
#include "../../Shaders/ShaderProgram.h"

class Transformation :public Composite {
protected:
    std::vector<Composite*> transformations;
    glm::mat4 M{1.f};

private:
    void action(glm::mat4 &p_M) override;

public:

    void action(ShaderProgram shader);

    void Add(Composite *composite) override ;
    void Remove(Composite *composite) override {

//        for(auto it = transformations.begin(); it != transformations.end(); it++){
//            if(*it == composite){
//                transformations.erase(it);
//
//                (*it)->parent = nullptr;
//                delete (*it);
//
//                break;
//            }
//        }

    }

    void Remove(int index);
};


#endif //TEST_TRANSFORMATION_H
