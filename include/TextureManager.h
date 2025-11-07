#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <memory>
#include <string>
#include <unordered_map>
#include "Texture.h"

class TextureManager {
public:
    static std::shared_ptr<Texture> load(const std::string& path, bool flip = true);

private:
    static std::unordered_map<std::string, std::weak_ptr<Texture>> cache;
};

#endif
