//
// Created by Filip on 11.11.2023.
//

#ifndef TEST_TEXTUREMODEL_H
#define TEST_TEXTUREMODEL_H


#include "Model.h"

class TextureModel : public Model {
public:
    TextureModel(float x, float y, float z, const float *modelVertices, size_t size);

    void accept(ModelVisitor &visitor) override;

    void draw() override;

    GLuint textureID;
};


#endif //TEST_TEXTUREMODEL_H
