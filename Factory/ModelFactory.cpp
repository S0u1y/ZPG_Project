//
// Created by wizzy on 17.10.2023.
//

#include "ModelFactory.h"

Shape *ModelFactory::createModel(const char *name, float x, float y, float z) {
    name = lower(name).c_str();
    if(compare(name, "sphere")){
        return new Sphere(x,y,z);
    }
    else if(compare(name, "plain")){
        return new Model(x,y,z, plain, sizeof(plain)/sizeof(plain[0]));
    }
    else if(compare(name, "suzi_flat")){
        return new Model(x,y,z, suziFlat, sizeof(suziFlat)/sizeof(suziFlat[0]));
    }
    else if(compare(name, "suzi_smooth")){
        return new Model(x,y,z, suziSmooth, sizeof(suziSmooth)/sizeof(suziSmooth[0]));
    }
    return nullptr;
}

bool ModelFactory::compare(const char *first, const char *second) {
    return strcmp(first, second) == 0;
}

//very crude tolower.. Will change to make it iterate through char*
//TODO change function to work with char*
std::string ModelFactory::lower(std::string in) {
    std::transform(in.begin(), in.end(), in.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    return in;
}
