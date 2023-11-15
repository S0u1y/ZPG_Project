//
// Created by Filip on 14.11.2023.
//

#include <iostream>
#include "CubemapTexture.h"

CubemapTexture::CubemapTexture(const char* posx, const char* negx, const char* posy, const char* negy, const char* posz, const char* negz, GLenum textureUnit, GLenum textureType)
: Texture(textureUnit, textureType)
{

    glActiveTexture(textureUnit);
    GLuint image = SOIL_load_OGL_cubemap(posx, negx, posy, negy, posz, negz, SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
    if (image == NULL) {
        std::cout << "An error occurred while loading CubeMap." << std::endl;
        exit(EXIT_FAILURE);
    }
    glBindTexture(textureType, image);
    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

}
