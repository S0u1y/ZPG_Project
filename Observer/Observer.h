//
// Created by wizzy on 18.10.23.
//

#ifndef TEST_OBSERVER_H
#define TEST_OBSERVER_H

template<typename T>
class Observer {
protected:
    T* subject;
public:
    void linkToSubject(T* subject){
        this->subject = subject;
    }
    virtual void onNotify() = 0;

    template<typename ...A>
    void onNotify(A... data) {};
};


#endif //TEST_OBSERVER_H
