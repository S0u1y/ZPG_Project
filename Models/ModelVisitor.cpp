//
// Created by Filip on 11.11.2023.
//

#include "ModelVisitor.h"

#include "Model.h"
#include "NoTextureModel.h"
#include "TextureModel.h"

void CreateModelVisitor::visitNoTextureModel(NoTextureModel &model) {
    auto &VAO = model.getVAO();
//    auto &VBO = model.getVBO();

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    model.generateVBO();

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*6, nullptr);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float)*6, (GLvoid *)(sizeof(float)*3));

}

void CreateModelVisitor::visitTextureModel(TextureModel &model) {
    auto &VAO = model.getVAO();
//    auto &VBO = model.getVBO();

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    model.generateVBO();

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*8, nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float)*8, (GLvoid *)(sizeof(float)*3));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float)*8, (GLvoid *)(sizeof(float)*6));
    glEnableVertexAttribArray(2);
}
