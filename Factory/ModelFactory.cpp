//
// Created by wizzy on 17.10.2023.
//

#include "ModelFactory.h"

#include "../Models/Sphere.h"
#include "../Models/tree.h"
#include "../Models/gift.h"
#include "../Models/bushes.h"
#include "../Models/suzi_flat.h"
#include "../Models/suzi_smooth.h"
#include "../Models/plain.h"

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
    else if(compare(name, "bushes")){
        return new Model(x,y,z, bushes, sizeof(bushes)/sizeof(bushes[0]));
    }
    else if(compare(name, "gift")){
        return new Model(x,y,z, gift, sizeof(gift)/sizeof(gift[0]));
    }
    else if(compare(name, "tree")){
        return new Model(x,y,z, tree, sizeof(tree)/sizeof(tree[0]));
    }
    printf("Could not find model \"%s\"\n", name);
    exit(-1);
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
