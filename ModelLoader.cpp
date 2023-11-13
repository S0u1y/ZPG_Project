//
// Created by Filip on 12.11.2023.
//

#include "ModelLoader.h"

unsigned int ModelLoader::importOptions = aiProcess_OptimizeMeshes | aiProcess_JoinIdenticalVertices | aiProcess_Triangulate | aiProcess_CalcTangentSpace;

const aiScene* ModelLoader::loadScene(const char *filePath){
    return importer.ReadFile(filePath, importOptions);
}
