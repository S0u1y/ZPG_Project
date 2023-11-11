//
// Created by Filip on 11.11.2023.
//

#ifndef TEST_MODELVISITOR_H
#define TEST_MODELVISITOR_H

class NoTextureModel; class TextureModel;

class ModelVisitor {
public:
    virtual void visitNoTextureModel(NoTextureModel& model) = 0;
    virtual void visitTextureModel(TextureModel& model) = 0;
};

class CreateModelVisitor : public ModelVisitor{
public:
    void visitNoTextureModel(NoTextureModel &model) override;
    void visitTextureModel(TextureModel &model) override;
};

#endif //TEST_MODELVISITOR_H
