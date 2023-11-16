//
// Created by wizzy on 16.11.23.
//

#ifndef TEST_MODELVERTICESHOLDER_H
#define TEST_MODELVERTICESHOLDER_H


#include <string>
#include <vector>
#include <unordered_map>

class ModelVerticesHolder{
private:
    ModelVerticesHolder() = default;
    static ModelVerticesHolder* instance;
public:
    std::unordered_map<std::string, std::vector<float>> vertices;

    const std::vector<float>& operator[](const std::string& key);
    static ModelVerticesHolder* getInstance();

//    TextureHolder() = delete;
    ModelVerticesHolder(const ModelVerticesHolder&) = delete;
    ModelVerticesHolder(ModelVerticesHolder&&) = delete;
    ~ModelVerticesHolder() = delete;

    const std::vector<float>& createVerticesFromFile(const char* name, const char* filepath);

};


#endif //TEST_MODELVERTICESHOLDER_H
