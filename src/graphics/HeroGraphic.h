#pragma once

#include "core/Graphic.h"

class Hero;
struct SDL_Texture;

class HeroGraphic : public Graphic {
public:
    HeroGraphic(TargetType target, Hero* explorer);

    void draw() const override;

private:
    Hero* m_pHero;
};