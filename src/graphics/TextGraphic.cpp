#include "TextGraphic.h"

#include "SDL_render.h"
#include "SDL_surface.h"
#include "SDL_ttf.h"

#include <cassert>

TextGraphic::TextGraphic(
    const std::string& text, TTF_Font* pFont, SDL_Renderer* pRenderer)
    : m_text(text), m_pRenderer(pRenderer), m_pFont(pFont) {
    assert(pFont);
    assert(pRenderer);

    m_pSurface = TTF_RenderText_Solid(m_pFont, m_text.c_str(), {255, 255, 255});
    m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, m_pSurface);
}
TextGraphic::~TextGraphic() {
    SDL_DestroyTexture(m_pTexture);
    SDL_FreeSurface(m_pSurface);
}

void TextGraphic::setText(const std::string& text) {
    if (m_text == text) return;
    m_text = text;
    m_pSurface = TTF_RenderText_Solid(m_pFont, m_text.c_str(), {255, 255, 255});
    m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, m_pSurface);
}
void TextGraphic::setColor(uint8_t r, uint8_t g, uint8_t b) {
    SDL_SetTextureColorMod(m_pTexture, r, g, b);
}

SDL_Point TextGraphic::getRenderSize() const {
    SDL_Point p;
    SDL_QueryTexture(m_pTexture, NULL, NULL, &p.x, &p.y);
    return p;
}
void TextGraphic::draw(RenderTarget target) const {
    SDL_Point size = getRenderSize();
    SDL_Rect dest = {m_dest.x, m_dest.y, size.x, size.y};
    SDL_RenderCopy(target, m_pTexture, NULL, &dest);
}