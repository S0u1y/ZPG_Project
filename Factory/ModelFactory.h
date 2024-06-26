//
// Created by wizzy on 17.10.2023.
//

#ifndef TEST_MODELFACTORY_H
#define TEST_MODELFACTORY_H

#include "../Models/Model.h"

#include <string>
#include <algorithm>
#include <cstring>


//basic creation of models..
//TODO add some list of string-object later.
class ModelFactory {
private:
    static bool isTextured;
    static bool compare(const char* first, const char* second);
    static std::string lower(std::string in);
    template<typename T>
    static Shape* createModelTemplated(const char* name, float x, float y, float z);
public:
    static Shape* createModel(const char* name, float x, float y, float z);
    static void setTextured(bool isTextured);
};


#endif //TEST_MODELFACTORY_H
