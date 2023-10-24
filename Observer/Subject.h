//
// Created by wizzy on 18.10.23.
//

#ifndef TEST_SUBJECT_H
#define TEST_SUBJECT_H

#include <list>
#include "Observer.h"

class Subject {
protected:
    std::list<Observer<Subject>*> observers;
public:
    void addObserver(Observer<Subject>* observer){

        observers.push_back(observer);
    }
    //I will burn in programmers' hell for this as well...
    void addObserver(void* observer){

        observers.push_back(reinterpret_cast<Observer<Subject> *>(observer));
    }
    void notify(){
        for (const auto &item: observers){
            item->onNotify();
        }
    }
    //we want to add functionality for multiple data..
    template<typename ...T>
    void notify(T... data){
        for (const auto &item: observers){
            item->onNotify(data...);
        }
    }
};


#endif //TEST_SUBJECT_H
