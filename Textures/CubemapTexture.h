//
// Created by Filip on 14.11.2023.
//

#ifndef TEST_CUBEMAPTEXTURE_H
#define TEST_CUBEMAPTEXTURE_H


#include "Texture.h"

class CubemapTexture : public Texture{
private:
//    void create(const char *filepath) override;

public:
    CubemapTexture(const char* posx, const char* negx, const char* posy, const char* negy, const char* posz, const char* negz, GLenum textureUnit, GLenum textureType);
};


#endif //TEST_CUBEMAPTEXTURE_H
