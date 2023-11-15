//
// Created by Filip on 14.11.2023.
//

#ifndef TEST_CUBEMAPMODEL_H
#define TEST_CUBEMAPMODEL_H


#include "Model.h"

class CubemapModel : public Model{
public:
    GLuint textureID;

    CubemapModel(float x, float y, float z, const float *modelVertices, size_t size);

    void draw() override;

    void accept(ModelVisitor &visitor) override;
};


#endif //TEST_CUBEMAPMODEL_H
