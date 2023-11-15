//
// Created by Filip on 28.10.2023.
//

#ifndef TEST_SCENES_H
#define TEST_SCENES_H
#include "../Scene.h"

#include <unordered_map>
class killmeplease;

class Scenes{
public:
    std::unordered_map<const char*, std::shared_ptr<Scene>> scenes{};
    ShaderProgramHolder shaderProgramHolder{};

    std::vector<shared_ptr<killmeplease>> composites;

    Scene* createScene(const char* name);

    virtual void initializeShaders();
    virtual void initialize();
    virtual void initializeTextures();
    Scene* operator[] (const char* name);
};


#endif //TEST_SCENES_H
