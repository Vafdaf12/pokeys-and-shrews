#include "Label.h"
using namespace ui;

#include "SDL_render.h"
#include "SDL_surface.h"
#include "SDL_ttf.h"

#include <cassert>

Label::Label(TargetType target, TTF_Font* pFont, const std::string& text)
    : Graphic(target), m_text(text), m_pFont(pFont) {
    assert(pFont);

    render();

    m_position = {0, 0};
    setColor(0, 0, 0);
}
Label::~Label() {
    if (m_pTexture) SDL_DestroyTexture(m_pTexture);
    if (m_pSurface) SDL_FreeSurface(m_pSurface);
}
Label::Label(const Label& rhs)
    : Graphic(rhs), m_text(rhs.m_text), m_pFont(rhs.m_pFont) {
    render();
}
Label::Label(Label&& rhs) : Graphic(rhs), m_pFont(rhs.m_pFont) {
    std::swap(m_text, rhs.m_text);
    std::swap(m_pSurface, rhs.m_pSurface);
    std::swap(m_pTexture, rhs.m_pTexture);
}
Label& Label::operator=(const Label& rhs) {
    setPosition(rhs.getPosition());
    m_text = rhs.m_text;
    m_pFont = rhs.m_pFont;
    m_target = rhs.m_target;

    render();

    return *this;
}
Label& Label::operator=(Label&& rhs) {
    setPosition(rhs.getPosition());
    std::swap(m_text, rhs.m_text);
    std::swap(m_pSurface, rhs.m_pSurface);
    std::swap(m_pTexture, rhs.m_pTexture);
    std::swap(m_target, rhs.m_target);
    return *this;
}

void Label::render() {
    SDL_Color col = {255, 255, 255};
    if (m_pTexture) {
        SDL_GetTextureColorMod(m_pTexture, &col.r, &col.g, &col.b);
        SDL_DestroyTexture(m_pTexture);
    }
    if (m_pSurface) SDL_FreeSurface(m_pSurface);

    m_pSurface = TTF_RenderText_Solid(m_pFont, m_text.c_str(), {255, 255, 255});
    m_pTexture = SDL_CreateTextureFromSurface(m_target, m_pSurface);
    SDL_SetTextureColorMod(m_pTexture, col.r, col.g, col.b);
}
void Label::setText(const std::string& text) {
    if (m_text == text) return;
    m_text = text;
    render();
}
void Label::setColor(uint8_t r, uint8_t g, uint8_t b) {
    SDL_SetTextureColorMod(m_pTexture, r, g, b);
}

SDL_Rect Label::getBoundingBox() const {
    SDL_Rect rect = {m_position.x, m_position.y, 0, 0};
    SDL_QueryTexture(m_pTexture, NULL, NULL, &rect.w, &rect.h);
    return rect;
}
void Label::draw() const {
    SDL_Rect dest = getBoundingBox();
    SDL_RenderCopy(m_target, m_pTexture, NULL, &dest);
}