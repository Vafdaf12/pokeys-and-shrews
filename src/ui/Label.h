#pragma once
#include "SDL_rect.h"
#include "SDL_surface.h"
#include "core/Graphic.h"

#include "SDL_ttf.h"

#include <string>

namespace ui {
class Label : public Graphic {
public:
    Label(TargetType target, TTF_Font* font, const std::string& text);
    ~Label();

    void draw() const override;

    // Move semantics
    Label(const Label&);
    Label(Label&&);
    Label& operator=(const Label&);
    Label& operator=(Label&&);

    SDL_Rect getBoundingBox() const;

    // Setters
    void setText(const std::string& text);
    void setTextColor(uint8_t r, uint8_t g, uint8_t b);

    // Getters
    inline const std::string& getText() const { return m_text; }

private:
    void render();

    std::string m_text;
    SDL_Surface* m_pSurface = nullptr;
    SDL_Texture* m_pTexture = nullptr;
    TTF_Font* m_pFont;
};

} // namespace ui