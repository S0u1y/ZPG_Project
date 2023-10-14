//
// Created by wizzy on 11.10.23.
//

#ifndef TEST_OBSERVER_H
#define TEST_OBSERVER_H

#include <vector>
#include <functional>

class Observer{
private:
    std::vector<std::function<void()>> functions;
public:

    void Add(const std::function<void()>& func){
        functions.push_back(func);
    }

    void onEvent(){
        for (const auto &item: functions){
            item();
        }
    }

};

#endif //TEST_OBSERVER_H
