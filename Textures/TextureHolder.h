//
// Created by wizzy on 13.11.23.
//

#ifndef TEST_TEXTUREHOLDER_H
#define TEST_TEXTUREHOLDER_H

#include <unordered_map>
#include <GL/glew.h>

class Texture;

//texture holder for accessing specific textures
//eg I want woodplanks - TextureHolder["Wood"]
class TextureHolder : public std::unordered_map<const char*, Texture>{
private:
    TextureHolder(){}
    static TextureHolder* instance;
public:

    static int createTexture(const char* name, const char* filepath, GLenum textureType);

    static TextureHolder* getInstance();

//    TextureHolder() = delete;
    TextureHolder(const TextureHolder&) = delete;
    TextureHolder(TextureHolder&&) = delete;
    ~TextureHolder() = delete;
};


#endif //TEST_TEXTUREHOLDER_H
