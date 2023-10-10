//
// Created by Filip on 08.10.2023.
//
//Za tohle pujdu do pekla.
//

#ifndef TEST_COMPOSITE_H
#define TEST_COMPOSITE_H

#include <vector>
#include "../Shader.h"


class Composite{
public:
    virtual void Add(Composite* composite) = 0;
    virtual void Remove(Composite* composite) = 0;

    virtual void action(glm::mat4 &M) = 0;

//    Composite* parent;
};

class Transformation: public Composite{
protected:
    std::vector<Composite*> transformations;
    glm::mat4 M{1.f};

private:
    void action(glm::mat4 &M) override{
        for(auto i = 0; i <  transformations.size(); i++){
            transformations[i]->action(this->M);
            delete transformations[i];
        }
        transformations.clear();
    }

public:

    void action(Shader shader){
        action(this->M);
        shader.setMatrixUniform("MVP", this->M);
    }

    void Add(Composite *composite) override {
        transformations.push_back(composite);
//        composite->parent = this;
    }

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

    void Remove(int index){
        auto it = transformations.begin()+index;

        delete (*it);

        transformations.erase(it);

//        (*it)->parent = nullptr;


    }

};

//leaf node(s)
class Rotation : public Composite{
private:
    float angle;
    glm::vec3 axis;


    void Add(Composite *composite) override {
    }
    void Remove(Composite *composite) override {
    }

public:
    Rotation(float angle, const glm::vec3 &axis) : angle(angle), axis(axis) {}

    void action(glm::mat4 &M) override {
        M = glm::rotate(M, angle, axis);
    }

};

class Move : public Composite{
private:
    glm::vec3 vector;


    void Add(Composite *composite) override {
    }
    void Remove(Composite *composite) override {
    }

public:
    Move(const glm::vec3 &vector) : vector(vector) {}

    void action(glm::mat4 &M) override {
        M = glm::translate(M, vector);
    }
};

#endif //TEST_COMPOSITE_H
