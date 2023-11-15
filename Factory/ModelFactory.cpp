//
// Created by wizzy on 17.10.2023.
//

#include "ModelFactory.h"

#include "../Models/tree.h"
#include "../Models/gift.h"
#include "../Models/bushes.h"
#include "../Models/suzi_flat.h"
#include "../Models/suzi_smooth.h"
#include "../Models/plain.h"
#include "../Models/sphere.h"
#include "../Models/texturedPlain.h"

#include "../Models/TextureModel.h"
#include "../Models/NoTextureModel.h"
#include "../Models/ModelVisitor.h"
#include "../Models/skycube.h"
#include "../Models/CubemapModel.h"

bool ModelFactory::isTextured = false;



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

void ModelFactory::setTextured(bool isTextured) {
    ModelFactory::isTextured = isTextured;
}

template<typename T>
Shape *ModelFactory::createModelTemplated(const char *name, float x, float y, float z) {
    T* newModel = nullptr;
    auto lowered_name = lower(name);
    name = lowered_name.c_str();
    if(!strcmp(name, "sphere")){
        newModel = new T(x,y,z, sphere, sizeof(sphere)/sizeof(sphere[0]));
    }
    else if(compare(name, "plain")){
        newModel = new T(x,y,z, plain, sizeof(plain)/sizeof(plain[0]));
    }
    else if(compare(name, "suzi_flat")){
        newModel = new T(x,y,z, suziFlat, sizeof(suziFlat)/sizeof(suziFlat[0]));
    }
    else if(compare(name, "suzi_smooth")){
        newModel = new T(x,y,z, suziSmooth, sizeof(suziSmooth)/sizeof(suziSmooth[0]));
    }
    else if(compare(name, "bushes")){
        newModel = new T(x,y,z, bushes, sizeof(bushes)/sizeof(bushes[0]));
    }
    else if(compare(name, "gift")){
        newModel = new T(x,y,z, gift, sizeof(gift)/sizeof(gift[0]));
    }
    else if(compare(name, "tree")){
        newModel = new T(x,y,z, tree, sizeof(tree)/sizeof(tree[0]));
    }
    if(newModel != nullptr){
        CreateModelVisitor visitor;
        newModel->accept(visitor);
        return newModel;
    }
    printf("Could not find model \"%s\"\n", name);
    exit(-1);
}
template<>
Shape *ModelFactory::createModelTemplated<TextureModel>(const char *name, float x, float y, float z) {

    TextureModel* newModel = nullptr;
    auto lowered_name = lower(name);
    name = lowered_name.c_str();
    if(compare(name, "plain")){
        newModel = new TextureModel(x,y,z, textured_plain, sizeof(textured_plain)/sizeof(textured_plain[0]));
    }
    if(compare(name, "sky_cube") || compare(name, "skycube")){
        auto newModel = new CubemapModel(x,y,z, skycube, sizeof(skycube)/sizeof(skycube[0]));
        CreateModelVisitor visitor;
        newModel->accept(visitor);
        return newModel;
    }
    if(newModel != nullptr){
        CreateModelVisitor visitor;
        newModel->accept(visitor);
        return newModel;
    }
    printf("Could not find textured model \"%s\"\n", name);
    exit(-1);
}

Shape *ModelFactory::createModel(const char *name, float x, float y, float z) {
    if (ModelFactory::isTextured){
        return createModelTemplated<TextureModel>(name, x, y, z);
    }
    return createModelTemplated<NoTextureModel>(name, x, y, z);
}