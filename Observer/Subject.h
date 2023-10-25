//
// Created by wizzy on 18.10.23.
//

#ifndef TEST_SUBJECT_H
#define TEST_SUBJECT_H

#include <list>
#include <vector>
#include "Observer.h"

template<typename T>
class Subject {
public:
    Subject() {}
    virtual ~Subject() {}
    void addObserver (Observer<T> *observer)
    {
        observers.push_back(observer);
    }
    void notify ()
    {
        for (const auto &item : observers){
            item->onNotify((T*)this);
        }
    }
private:
    std::vector<Observer<T> *> observers;
};


#endif //TEST_SUBJECT_H
