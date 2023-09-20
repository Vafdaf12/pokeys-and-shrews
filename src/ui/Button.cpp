#include "Button.h"
#include "SDL_events.h"
#include "SDL_mouse.h"
#include "SDL_rect.h"
#include "SDL_render.h"
#include "ui/Label.h"
#include <concepts>

using namespace ui;

Button::Button(TargetType target, TTF_Font* pFont, EventLoop& loop)
    : Label(target, pFont, "") {

    loop.onMouseUp(SDL_BUTTON_LEFT, [&](SDL_Event ev) {
        int x = ev.button.x;
        int y = ev.button.y;
        SDL_Rect rect = this->getBoundingBox();

        if (x < rect.x) return;
        if (y < rect.y) return;
        if (x > rect.x + rect.w) return;
        if (y > rect.y + rect.h) return;

        m_onClick();
    });
}
void Button::draw() const {
    SDL_Rect rect = getBoundingBox();
    SDL_SetRenderDrawColor(
        m_target, m_background.r, m_background.g, m_background.b, 255);
    SDL_RenderFillRect(m_target, &rect);

    Label::draw();
}