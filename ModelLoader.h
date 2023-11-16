//
// Created by Filip on 12.11.2023.
//

#ifndef TEST_MODELLOADER_H
#define TEST_MODELLOADER_H

#include <assimp/scene.h> // aiScene output data structure
#include <assimp/postprocess.h>
#include "assimp/Importer.hpp"

#include <memory>
#include <vector>

//TODO make a ModelHolder class
class ModelLoader {
public:
    static Assimp::Importer importer;
    static unsigned int importOptions;

    static std::vector<float> getVertices(const char* filepath);
};


#endif //TEST_MODELLOADER_H
