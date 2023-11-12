//
// Created by Filip on 12.11.2023.
//

#ifndef TEST_TEXTURE_H
#define TEST_TEXTURE_H

#include "SOIL.h"
#include "GL/glew.h"

class Texture {
private:
    GLuint id;
    int textureUnit{-1};
public:
    Texture(const char* filepath, int textureUnit);
};


#endif //TEST_TEXTURE_H
