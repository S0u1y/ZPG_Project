//
// Created by Filip on 29.10.2023.
//

#include "killmeplease.h"


void killmeplease::action(glm::mat4 &M) {
    for(auto & transformation : transformations){
        transformation->action(this->M);
    }
}

void killmeplease::action() {
    if (transformations.empty()) return;

    action(this->M);
    for (const auto &item : shapes){
        item->transformation.setTransform(M);
    }
    transformations.clear();
//    this->M = glm::mat4{1.f};
}

void killmeplease::Add(Composite *composite) {
    Transformation::Add(composite);
}

void killmeplease::Remove(Composite *composite) {
    Transformation::Remove(composite);
}
