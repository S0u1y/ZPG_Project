//
// Created by Filip on 14.10.2023.
//

#include "Transformation.h"

void Transformation::action(glm::mat4 &p_M) {
    for(auto i = 0; i <  transformations.size(); i++){
        transformations[i]->action(this->M);
        delete transformations[i];
    }
    transformations.clear();
}

void Transformation::action(Shader shader) {
    action(this->M);
    shader.setMatrixUniform("MVP", this->M);
}

void Transformation::Add(Composite *composite) {
    transformations.push_back(composite);
//        composite->parent = this;

}

void Transformation::Remove(int index) {
    auto it = transformations.begin()+index;

    delete (*it);

    transformations.erase(it);

//        (*it)->parent = nullptr;


}