#pragma once

#include "core/Graphic.h"

#include "SDL_render.h"
#include "SDL_ttf.h"
#include <string>

class TextGraphic : public Graphic {
public:
    TextGraphic(
        const std::string& text, TTF_Font* pFont, SDL_Renderer* pRenderer);
    ~TextGraphic();

    SDL_Point getRenderSize() const;

    void draw(RenderTarget target) const override;

    void setText(const std::string& text);
    inline const std::string& getText() const { return m_text; }

    inline void setPosition(int x, int y) { m_dest = {x, y}; }
    void setColor(uint8_t r, uint8_t g, uint8_t b);

private:
    std::string m_text;

    SDL_Renderer* m_pRenderer;
    SDL_Surface* m_pSurface;
    SDL_Texture* m_pTexture;
    SDL_Point m_dest;

    TTF_Font* m_pFont;
};