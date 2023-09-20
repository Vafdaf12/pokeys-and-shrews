
#include "Button.h"
#include "SDL_mouse.h"
#include "SDL_render.h"
#include <stdio.h>
using namespace ui;

Button::Button(TargetType target,
    TTF_Font* font,
    EventLoop& eventLoop,
    const std::string& text)
    : Label(target, font, text) {

    eventLoop.onMouseUp(SDL_BUTTON_LEFT, [=](SDL_Event e) {
        SDL_Rect bb = this->getBoundingBox();
        int x = e.button.x;
        int y = e.button.y;

        if (x < bb.x) return;
        if (y < bb.y) return;
        if (x > bb.x + bb.w) return;
        if (y > bb.y + bb.h) return;
        if (m_onClick) m_onClick();
    });
}

void Button::draw() const {
    SDL_Rect r = getBoundingBox();
    SDL_SetRenderDrawColor(m_target,
        m_background.r,
        m_background.g,
        m_background.b,
        m_background.a);
    SDL_RenderDrawRect(m_target, &r);
    Label::draw();
}