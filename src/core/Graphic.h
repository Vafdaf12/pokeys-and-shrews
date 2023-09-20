#pragma once

#include "SDL_rect.h"
#include <cassert>

struct SDL_Renderer;

class Graphic {
public:
    using TargetType = SDL_Renderer*;
    using Vector = SDL_Point;

    Graphic(TargetType target, Vector pos = {0, 0})
        : m_position(pos), m_target(target) {
        assert(target);
    }

    virtual ~Graphic() {}
    virtual void draw() const = 0;
    virtual void update(uint32_t dt) {}

    inline void setPosition(Vector pos) { m_position = pos; }
    inline Vector getPosition() const { return m_position; }

protected:
    Vector m_position = {0, 0};
    TargetType m_target;
};