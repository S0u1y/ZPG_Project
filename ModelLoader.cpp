//
// Created by Filip on 12.11.2023.
//

#include "ModelLoader.h"



unsigned int ModelLoader::importOptions = aiProcess_OptimizeMeshes | aiProcess_JoinIdenticalVertices | aiProcess_Triangulate | aiProcess_CalcTangentSpace;
Assimp::Importer ModelLoader::importer = Assimp::Importer();

std::vector<float> ModelLoader::getVertices(const char* filepath) {
    auto scene = ModelLoader::importer.ReadFile(filepath, importOptions);
    if(!scene){
        printf("An error occured while loading model.\n");
        exit(EXIT_FAILURE);
    }

    std::vector<float> output;

    auto mesh = scene->mMeshes[0];

    auto count = mesh->mNumFaces;

    for (int i = 0; i < mesh->mNumFaces; ++i) {
        auto Face = mesh->mFaces[i];

        for (int j = 0; j < 3; ++j) {

            int id = Face.mIndices[j];

            auto pos = mesh->mVertices[id];
            output.push_back(pos.x);output.push_back(pos.y);output.push_back(pos.z);

            auto nor = mesh->mNormals[id];
            output.push_back(nor.x);output.push_back(nor.y);output.push_back(nor.z);

            auto uv = mesh->mTextureCoords[0][id];
            output.push_back(uv.x);output.push_back(uv.y);

        }

    }

    return output;
}
