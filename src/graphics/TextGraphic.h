#pragma once

#include "core/Graphic.h"

#include "SDL_render.h"
#include "SDL_ttf.h"
#include <string>

class TextGraphic : public Graphic {
public:
    TextGraphic(TargetType target, const std::string& text, TTF_Font* pFont);
    ~TextGraphic();

    SDL_Point getRenderSize() const;

    void draw() const override;

    void setText(const std::string& text);
    inline const std::string& getText() const { return m_text; }

    void setColor(uint8_t r, uint8_t g, uint8_t b);

private:
    void renderText();
    std::string m_text;

    SDL_Surface* m_pSurface = nullptr;
    SDL_Texture* m_pTexture = nullptr;

    TTF_Font* m_pFont;
};