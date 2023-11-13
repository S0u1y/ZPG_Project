//
// Created by Filip on 12.11.2023.
//

#ifndef TEST_MODELLOADER_H
#define TEST_MODELLOADER_H

#include <assimp/scene.h> // aiScene output data structure
#include <assimp/postprocess.h>
#include "assimp/Importer.hpp"

class ModelLoader {
public:
    static Assimp::Importer importer;
    static unsigned int importOptions;

    static const aiScene* loadScene(const char* filePath);
};


#endif //TEST_MODELLOADER_H
