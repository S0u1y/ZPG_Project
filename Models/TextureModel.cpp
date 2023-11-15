//
// Created by Filip on 11.11.2023.
//

#include "TextureModel.h"
#include "ModelVisitor.h"

void TextureModel::accept(ModelVisitor &visitor) {
    visitor.visitTextureModel(*this);
}

TextureModel::TextureModel(float x, float y, float z, const float *modelVertices, size_t size)
: Model(x, y, z,modelVertices,size)
{
    if(size%8){
        printf("Bad vertices array! Array has to consist of rows that are 8 long.\n");
        exit(-1);
    }
}

void TextureModel::draw() {
    Model::draw();
    shader->setUniform("textureUnitID", (int)textureID);
    // draw triangles
    glDrawArrays(GL_TRIANGLES, 0, size/8); //mode,first,count
}
