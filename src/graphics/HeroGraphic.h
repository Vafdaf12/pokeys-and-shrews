#pragma once

#include "core/Graphic.h"
#include "tweeny.h"

class Hero;
struct SDL_Texture;

class HeroGraphic : public Graphic {
public:
    HeroGraphic(TargetType target, Hero* explorer);

    void draw() const override;
    void update(uint32_t dt) override;

private:
    tweeny::tween<int, int> m_current =
        tweeny::from(-1, -1).to(-1, -1).during(2000);
    Hero* m_pHero;
};