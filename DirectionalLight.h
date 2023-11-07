//
// Created by Filip on 07.11.2023.
//

#ifndef TEST_DIRECTIONALLIGHT_H
#define TEST_DIRECTIONALLIGHT_H


#include "Light.h"

class DirectionalLight : public Light{
public:
    DirectionalLight(const glm::vec3 &position, const glm::vec3 &direction, float angle);

//    void onNotify(){
//        for (const auto &item : observers){
//            item->onNotify((DirectionalLight*)this);
//        }
//    }

};


#endif //TEST_DIRECTIONALLIGHT_H
