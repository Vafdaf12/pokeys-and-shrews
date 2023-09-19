#pragma once

#include <cassert>

struct SDL_Renderer;

class Graphic {
public:
    using TargetType = SDL_Renderer*;

    Graphic(TargetType target) : m_target(target) { assert(target); }

    virtual ~Graphic() {}
    virtual void draw() const = 0;

protected:
    TargetType m_target;
};