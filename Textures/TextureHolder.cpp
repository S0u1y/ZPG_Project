//
// Created by wizzy on 13.11.23.
//

#include "TextureHolder.h"
#include "CubemapTexture.h"

TextureHolder* TextureHolder::instance = nullptr;

TextureHolder* TextureHolder::getInstance() {

    if (TextureHolder::instance == nullptr){
        TextureHolder::instance = new TextureHolder();
    }

    return TextureHolder::instance;
}

int TextureHolder::createTexture(const char* name, const char *filepath, GLenum textureType) {

    getInstance()->emplace(name, new Texture(filepath, GL_TEXTURE0 + getInstance()->size(), textureType));

    return getInstance()->size() - 1;
}

int
TextureHolder::createCubemap(const char *name, const char *posx, const char *negx, const char *posy, const char *negy,
                             const char *posz, const char *negz, GLenum textureType) {

    getInstance()->emplace(name, new CubemapTexture(posx, negx, posy, negy, posz, negz, GL_TEXTURE0 + getInstance()->size(), textureType));

    return getInstance()->size() - 1;
}

int TextureHolder::createCubemap(const std::string &name, const std::string &posx, const std::string &negx,
                                 const std::string &posy, const std::string &negy, const std::string &posz,
                                 const std::string &negz, GLenum textureType) {

    getInstance()->emplace(name, new CubemapTexture(posx.c_str(), negx.c_str(), posy.c_str(), negy.c_str(), posz.c_str(), negz.c_str(), GL_TEXTURE0 + getInstance()->size(), textureType));

    return getInstance()->size() - 1;
}

Texture* TextureHolder::operator[](const std::string& key) {
    for (const auto &item: *getInstance()){
        if(item.first == key)
            return item.second.get();
    }

    printf("No texture with key \"%s\" could be found.", key.c_str());
    return nullptr;
}
