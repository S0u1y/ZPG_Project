//
// Created by Filip on 29.10.2023.
//

#include "killmeplease.h"


void killmeplease::action(glm::mat4 &M) {}

void killmeplease::action() {
    Transformation::action(M);
    for (const auto &item : shapes){
        item->transformation.setTransform(M);
    }
}

void killmeplease::Add(Composite *composite) {
    Transformation::Add(composite);
}

void killmeplease::Remove(Composite *composite) {
    Transformation::Remove(composite);
}
