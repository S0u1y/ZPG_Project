//
// Created by Filip on 12.11.2023.
//

#ifndef TEST_TEXTURE_H
#define TEST_TEXTURE_H

#include "SOIL/SOIL.h"
#include "GL/glew.h"

class Texture {
private:
    GLuint id;
    GLenum textureUnit{0};
    GLenum textureType{0};
public:
    Texture(const char* filepath, GLenum textureUnit, GLenum textureType);

    GLenum getTextureUnit(){
        return textureUnit;
    }

    void activate();
    void unbind();
};


#endif //TEST_TEXTURE_H
