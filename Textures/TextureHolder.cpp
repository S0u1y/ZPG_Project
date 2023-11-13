//
// Created by wizzy on 13.11.23.
//

#include "TextureHolder.h"
#include "Texture.h"

TextureHolder* TextureHolder::instance = nullptr;

int TextureHolder::createTexture(const char* name, const char *filepath, GLenum textureType) {
    Texture texture(filepath, GL_TEXTURE0 + getInstance()->size(), textureType);
    getInstance()->emplace(name, texture);
    return getInstance()->size();
}

TextureHolder* TextureHolder::getInstance() {
    if (TextureHolder::instance != nullptr){
        TextureHolder::instance = new TextureHolder();
    }
    return TextureHolder::instance;
}
