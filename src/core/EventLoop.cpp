#include "EventLoop.h"
#include "SDL_events.h"

void EventLoop::handleEvent(EventType event) {
    if (event.type == SDL_QUIT) {
        m_shouldQuit = true;
    }
    for (auto& [type, handler] : m_handlers) {
        if (type != event.type) continue;
        handler(event);
    }
    for (auto& [type, btn, handler] : m_buttonHandlers) {
        if (type != event.type) continue;
        if (btn & BUTTON_LEFT && event.button.button == SDL_BUTTON_LEFT)
            handler(event);
        if (btn & BUTTON_RIGHT && event.button.button == SDL_BUTTON_RIGHT)
            handler(event);
    }
    for (auto& [type, key, handler] : m_keyHandlers) {
        if (type != event.type) continue;
        if (event.key.keysym.sym != key) continue;
        handler(event);
    }
}

void EventLoop::onMouseDown(MouseButton btn, EventHandler h) {
    m_buttonHandlers.emplace_back(SDL_MOUSEBUTTONDOWN, btn, h);
}
void EventLoop::onMouseUp(MouseButton btn, EventHandler h) {
    m_buttonHandlers.emplace_back(SDL_MOUSEBUTTONUP, btn, h);
}
void EventLoop::onKeyPressed(Key k, EventHandler h) {
    m_keyHandlers.emplace_back(SDL_KEYUP, k, h);
}
void EventLoop::onQuit(EventHandler h) { m_handlers.emplace_back(SDL_QUIT, h); }