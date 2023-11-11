//
// Created by Filip on 11.11.2023.
//

#include "NoTextureModel.h"
#include "ModelVisitor.h"

void NoTextureModel::accept(ModelVisitor &visitor) {
    visitor.visitNoTextureModel(*this);
}

NoTextureModel::NoTextureModel(float x, float y, float z, const float *modelVertices, size_t size)
: Model(x, y, z,modelVertices,size)
{
}

void NoTextureModel::draw() {
    Model::draw();
    // draw triangles
    glDrawArrays(GL_TRIANGLES, 0, size/6); //mode,first,count
}
