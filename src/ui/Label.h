#pragma once
#include "SDL_rect.h"
#include "core/Graphic.h"

#include "SDL_ttf.h"

#include <string>

namespace ui {

class Label : public Graphic {
public:
    Label(TargetType target, TTF_Font* pFont, const std::string& text);
    ~Label();

    Label(const Label&);
    Label(Label&&);
    Label& operator=(const Label&);
    Label& operator=(Label&&);

    void draw() const override;

    void setText(const std::string& text);
    void setColor(uint8_t r, uint8_t g, uint8_t b);

    SDL_Rect getBoundingBox() const;
    inline const std::string& getText() const { return m_text; }

private:
    void render();

    std::string m_text;

    SDL_Surface* m_pSurface = nullptr;
    SDL_Texture* m_pTexture = nullptr;

    TTF_Font* m_pFont;
};

} // namespace ui
