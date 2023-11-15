//
// Created by Filip on 14.11.2023.
//

#include "CubemapModel.h"
#include "ModelVisitor.h"
#include "../Camera.h"

CubemapModel::CubemapModel(float x, float y, float z, const float *modelVertices, size_t size)
        : Model(x, y, z, modelVertices, size) {}

void CubemapModel::accept(ModelVisitor &visitor) {
    visitor.visitCubeMapModel(*this);
}

void CubemapModel::draw() {

    Model::draw();
    shader->setUniform("textureUnitID", (int)this->textureID);
    // draw triangles
    glDrawArrays(GL_TRIANGLES, 0, size); //mode,first,count

    glClear(GL_DEPTH_BUFFER_BIT);
}
