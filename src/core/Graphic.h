#pragma once

struct SDL_Renderer;

class Graphic {
public:
    using TargetType = SDL_Renderer*;

    virtual ~Graphic() {}
    virtual void draw(TargetType target) const = 0;
};