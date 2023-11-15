//
// Created by Filip on 12.11.2023.
//

#ifndef TEST_TEXTURE_H
#define TEST_TEXTURE_H

#include "SOIL/SOIL.h"
#include "GL/glew.h"

class Texture {
protected:
//    GLuint id{0};
    GLenum textureUnit{0};
    GLenum textureType{0};

    //different types of textures may need these, but for the end user we don't want these to be accessible..
    Texture(GLenum textureUnit, GLenum textureType): textureUnit(textureUnit), textureType(textureType) {};
    Texture() = default;

//    virtual void create(const char* filepath) = 0;
public:
    Texture(const char* filepath, GLenum textureUnit, GLenum textureType);


    virtual GLenum getTextureUnit(){
        return textureUnit - GL_TEXTURE0;
    }


    void activate();
    void unbind();
};


#endif //TEST_TEXTURE_H
