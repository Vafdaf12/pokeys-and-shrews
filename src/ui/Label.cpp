#include "Label.h"

#include "SDL_render.h"
#include <utility>

using namespace ui;
Label::Label(TargetType target, TTF_Font* font, const std::string& text)
    : Graphic(target), m_text(text), m_pFont(font) {
    assert(font);
    render();
    setTextColor(0, 0, 0);
}

Label::~Label() {
    if (m_pTexture) SDL_DestroyTexture(m_pTexture);
    if (m_pSurface) SDL_FreeSurface(m_pSurface);
}

void Label::draw() const {
    SDL_Rect rect = getBoundingBox();
    SDL_RenderCopy(m_target, m_pTexture, NULL, &rect);
}

// Move semantics
Label::Label(const Label& rhs) : Label(rhs.m_target, rhs.m_pFont, rhs.m_text) {
    m_position = rhs.m_position;
    uint8_t r, g, b;
    render();
    SDL_GetTextureColorMod(m_pTexture, &r, &g, &b);
    setTextColor(r, g, b);
}
Label::Label(Label&& rhs) : Graphic(rhs) {
    m_text = std::move(rhs.m_text);

    m_pFont = rhs.m_pFont;
    m_pSurface = rhs.m_pSurface;
    m_pTexture = rhs.m_pTexture;

    rhs.m_pSurface = nullptr;
    rhs.m_pTexture = nullptr;
}
Label& Label::operator=(const Label& rhs) {
    if (&rhs == this) return *this;
    bool shouldRender = m_text != rhs.m_text || m_pFont != rhs.m_pFont;

    m_text = rhs.m_text;
    m_pFont = rhs.m_pFont;
    if (shouldRender) render();

    return *this;
}
Label& Label::operator=(Label&& rhs) {
    if (&rhs == this) return *this;
    m_text = std::move(rhs.m_text);

    m_pFont = rhs.m_pFont;
    m_pSurface = rhs.m_pSurface;
    m_pTexture = rhs.m_pTexture;

    rhs.m_pSurface = nullptr;
    rhs.m_pTexture = nullptr;

    return *this;
}

SDL_Rect Label::getBoundingBox() const {
    SDL_Rect r = {m_position.x, m_position.y, 0, 0};
    SDL_QueryTexture(m_pTexture, NULL, NULL, &r.w, &r.h);
    return r;
}

void Label::setText(const std::string& text) {
    if (m_text == text) return;
    m_text = text;
    render();
}
void Label::setTextColor(uint8_t r, uint8_t g, uint8_t b) {
    SDL_SetTextureColorMod(m_pTexture, r, g, b);
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