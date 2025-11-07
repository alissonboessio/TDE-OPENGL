#include "TextureManager.h"

std::unordered_map<std::string, std::weak_ptr<Texture>> TextureManager::cache;

std::shared_ptr<Texture> TextureManager::load(const std::string& path, bool flip) {
    auto it = cache.find(path);
    if (it != cache.end()) {
        if (auto existing = it->second.lock()) {
            return existing;
        }
    }

    auto tex = std::make_shared<Texture>(path, flip);
    cache[path] = tex;
    return tex;
}
