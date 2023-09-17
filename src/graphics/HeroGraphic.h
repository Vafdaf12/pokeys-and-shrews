#pragma once

#include "core/Graphic.h"

class Hero;
struct SDL_Texture;

class HeroGraphic : public Graphic {
public:
    HeroGraphic(Hero* explorer);

    void draw(TargetType target) const override;

private:
    Hero* m_pHero;
};