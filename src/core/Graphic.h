#pragma once

struct SDL_Renderer;

using RenderTarget = SDL_Renderer*;

class Graphic {
public:
    virtual ~Graphic() {}
    virtual void draw(RenderTarget target) const = 0;
};