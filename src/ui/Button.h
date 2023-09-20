#pragma once

#include "core/EventLoop.h"
#include "ui/Label.h"
#include <functional>
#include <stdint.h>

namespace ui {
class Button : public Label {
public:
    using ClickHandler = std::function<void()>;

    Button(TargetType target,
        TTF_Font* font,
        EventLoop& eventLoop,
        const std::string& text);

    void draw() const override;

    inline void setBackground(
        uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) {
        m_background = {r, g, b, a};
    }
    inline void onClick(ClickHandler h) { m_onClick = h; }

private:
    SDL_Color m_background;
    ClickHandler m_onClick;
};
} // namespace ui