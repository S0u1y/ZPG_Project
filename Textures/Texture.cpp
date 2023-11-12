//
// Created by Filip on 12.11.2023.
//

#include <cstdio>
#include <cstdlib>
#include "Texture.h"

Texture::Texture(const char *filepath, int textureUnit)
: textureUnit(textureUnit)
{
    //      activate texture we want to set
    glActiveTexture(textureUnit);
    GLuint image = SOIL_load_OGL_texture("Sources/wooden_fence.png", SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    if(image == NULL){
        printf("SOMETHING WENT WRONG\n");
        exit(-1);
    }
    //set image to texture
    glBindTexture(GL_TEXTURE_2D, image);
}
