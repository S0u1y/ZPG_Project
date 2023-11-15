//
// Created by wizzy on 13.11.23.
//

#ifndef TEST_TEXTUREHOLDER_H
#define TEST_TEXTUREHOLDER_H

#include <unordered_map>
#include <GL/glew.h>
#include <memory>

#include "Texture.h"

//texture holder for accessing specific textures
//eg I want woodplanks - TextureHolder["Wood"]
class TextureHolder : public std::unordered_map<std::string, std::unique_ptr<Texture>>{
private:
    TextureHolder() = default;
    static TextureHolder* instance;
public:

    static int createTexture(const char* name, const char* filepath, GLenum textureType);
    static int createCubemap(const char* name, const char* posx, const char* negx, const char* posy, const char* negy, const char* posz, const char* negz, GLenum textureType);
    static int createCubemap(const std::string& name, const std::string& posx, const std::string& negx, const std::string& posy, const std::string& negy, const std::string& posz, const std::string& negz, GLenum textureType);
    Texture* operator[](const std::string& key);
    static TextureHolder* getInstance();


//    TextureHolder() = delete;
    TextureHolder(const TextureHolder&) = delete;
    TextureHolder(TextureHolder&&) = delete;
    ~TextureHolder() = delete;
};


#endif //TEST_TEXTUREHOLDER_H
