#pragma once

#include "SDL_events.h"
#include "SDL_mouse.h"
#include <functional>
#include <stdint.h>

class EventLoop {
public:
    using EventType = SDL_Event;
    using EventHandler = std::function<void(SDL_Event)>;
    using MouseButton = uint8_t;
    using Key = SDL_KeyCode;

    void handleEvent(EventType event);

    void onMouseDown(MouseButton, EventHandler);
    void onMouseUp(MouseButton, EventHandler);
    void onKeyPressed(Key, EventHandler);
    void onQuit(EventHandler);

    inline bool shouldQuit() const { return m_shouldQuit; }

    const static MouseButton BUTTON_LEFT = 1 << 0;
    const static MouseButton BUTTON_RIGHT = 1 << 1;

private:
    bool m_shouldQuit = false;
    std::vector<std::pair<SDL_EventType, EventHandler>> m_handlers;
    std::vector<std::tuple<SDL_EventType, MouseButton, EventHandler>>
        m_buttonHandlers;
    std::vector<std::tuple<SDL_EventType, Key, EventHandler>> m_keyHandlers;
};