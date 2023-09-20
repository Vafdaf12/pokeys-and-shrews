#pragma once

#include "SDL_pixels.h"
#include "core/EventLoop.h"
#include "core/Graphic.h"
#include "ui/Label.h"

#include <functional>

namespace ui {

class Button : public Label {
public:
    Button(TargetType target, TTF_Font* pFont, EventLoop& loop);
    using ClickHandler = std::function<void()>;

    void draw() const override;

    inline void setBackground(uint8_t r, uint8_t g, uint8_t b) {
        m_background = {r, g, b};
    }
    inline void onClick(ClickHandler handler) { m_onClick = handler; }

private:
    SDL_Color m_background;

    ClickHandler m_onClick;
};
} // namespace ui