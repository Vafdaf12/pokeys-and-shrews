#pragma once

#include <string>
#include <unordered_map>
#include <utility>

#include "SDL_image.h"
#include "SDL_ttf.h"

class ResourceManager {
public:
    using FontType = TTF_Font*;
    using ImageType = SDL_Surface*;

    ResourceManager();
    ~ResourceManager();

    static ResourceManager& instance() { return s_instance; }

    FontType loadFont(const std::string& filename, int size = 12);
    ImageType loadImage(const std::string& filename);
    const std::string& getBasePath() { return m_basePath; }

private:
    static ResourceManager s_instance;
    std::string m_basePath;
    std::unordered_map<std::string, FontType> m_fonts;
    std::unordered_map<std::string, ImageType> m_images;
};