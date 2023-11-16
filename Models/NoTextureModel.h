//
// Created by Filip on 11.11.2023.
//

#ifndef TEST_NOTEXTUREMODEL_H
#define TEST_NOTEXTUREMODEL_H


#include "Model.h"

class NoTextureModel : public Model{
public:
    NoTextureModel(float x, float y, float z, const float *modelVertices, size_t size);

    NoTextureModel(float x, float y, float z, vector<float> modelVertices);

    void accept(ModelVisitor &visitor) override;

    void draw() override;

};


#endif //TEST_NOTEXTUREMODEL_H
