#include "ResourceManager.h"

#include "SDL_filesystem.h"

#include <cassert>
#include <string>

ResourceManager ResourceManager::s_instance;

ResourceManager::ResourceManager() { m_basePath = SDL_GetBasePath(); }
ResourceManager::FontType ResourceManager::loadFont(
    const std::string& filename, int size) {
    std::string key = std::to_string(size) + filename;
    if (m_fonts.empty()) {
        assert(TTF_Init() == 0);
    }

    if (!m_fonts.contains(key)) {
        std::string path = m_basePath + "res/" + filename;
        m_fonts[key] = TTF_OpenFont(path.c_str(), size);
    }
    return m_fonts[key];
}
ResourceManager::ImageType ResourceManager::loadImage(
    const std::string& filename) {
    std::string key = filename;

    if (!m_images.contains(key)) {
        std::string path = m_basePath + "res/" + filename;
        m_images[key] = IMG_Load(path.c_str());
    }
    return m_images[key];
}
ResourceManager::~ResourceManager() {
    for (auto font : m_fonts) {
        TTF_CloseFont(font.second);
    }
    for (auto img : m_images) {
        SDL_FreeSurface(img.second);
    }

    if (!m_fonts.empty()) {
        TTF_Quit();
    }
}