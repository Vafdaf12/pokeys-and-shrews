#pragma once

#include "SDL_rect.h"
#include "core/Graphic.h"

class Lair;

class LairGraphic : public Graphic {
public:
    LairGraphic(Lair* lair) : m_lair(lair) {}
    void draw(RenderTarget target) const override;

private:
    static constexpr SDL_Point START_POINT = {10, 10};

    Lair* m_lair;
};