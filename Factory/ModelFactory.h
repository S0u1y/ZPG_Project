//
// Created by Filip on 17.10.2023.
//

#ifndef TEST_MODELFACTORY_H
#define TEST_MODELFACTORY_H

#include "../Models/Sphere.h"
#include "../Models/Square.h"
#include "../Models/suzi_flat.h"
#include "../Models/suzi_smooth.h"
#include "../Models/plain.h"

#include "../Models/Model.h"

#include <string>
#include <algorithm>
#include <cstring>


//basic creation of models..
//TODO add some list of string-object later.
class ModelFactory {
private:
    static bool compare(const char* first, const char* second);
    static std::string lower(std::string in);
public:
    static Shape* createModel(const char* name, float x, float y, float z);
};


#endif //TEST_MODELFACTORY_H
