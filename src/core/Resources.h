#pragma once

#include "raylib.h"

#include <string>
#include <unordered_map>

class Resources {
public:
    static Texture2D getTexture(const std::string& path) {
        if (m_textures.find(path) == m_textures.end()) {
            m_textures[path] = LoadTexture(path.c_str());
        }
        return m_textures[path];
    }

private:
    static std::unordered_map<std::string, Texture2D> m_textures;
};
std::unordered_map<std::string, Texture2D> Resources::m_textures;