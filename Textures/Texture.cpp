//
// Created by Filip on 12.11.2023.
//

#include <cstdio>
#include <cstdlib>
#include "Texture.h"

Texture::Texture(const char *filepath, GLenum textureUnit, GLenum textureType)
: textureUnit(textureUnit), textureType(textureType)
{
    //      activate texture we want to set
    glActiveTexture(textureUnit);
    GLuint image = SOIL_load_OGL_texture(filepath, SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    if(image == NULL){
        printf("Error while loading texture.\n");
        exit(-1);
    }
    //set image to texture
    glBindTexture(textureType, image);
}

void Texture::activate() {
    glActiveTexture(textureUnit);
}

void Texture::unbind() {
    glActiveTexture(-1);
}
