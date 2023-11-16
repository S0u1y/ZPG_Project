//
// Created by wizzy on 16.11.23.
//

#include <cstring>
#include "ModelVerticesHolder.h"
#include "../ModelLoader.h"

ModelVerticesHolder* ModelVerticesHolder::instance = nullptr;

const std::vector<float> &ModelVerticesHolder::operator[](const std::string &key) {
    for (const auto &item: vertices){
        if(!strcmp(item.first.c_str(), key.c_str())){
            return item.second;
        }
    }

    printf("No Model Vertices indexed \"%s\"\n", key.c_str());
    exit(-1);
}

ModelVerticesHolder *ModelVerticesHolder::getInstance() {
    if(ModelVerticesHolder::instance == nullptr)
        ModelVerticesHolder::instance = new ModelVerticesHolder;

    return ModelVerticesHolder::instance;
}

const std::vector<float> &ModelVerticesHolder::createVerticesFromFile(const char* name, const char *filepath) {
    auto vertices = ModelLoader::getVertices(filepath);

    auto rt_pair = getInstance()->vertices.emplace(name, vertices);
    if(rt_pair.second){
        return rt_pair.first->second;
    }

    printf("There was an error while creating model vertices.\n");
    exit(-1);
}
