//
// Created by wizzy on 18.10.23.
//

#ifndef TEST_OBSERVER_H
#define TEST_OBSERVER_H

template<typename T>
class Observer {
protected:
public:
    virtual void onNotify() = 0;
    virtual void onNotify(T* subject) = 0;
};


#endif //TEST_OBSERVER_H
