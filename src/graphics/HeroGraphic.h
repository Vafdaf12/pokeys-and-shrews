#pragma once

#include "core/Graphic.h"
#include "tweeny.h"

class Hero;

class HeroGraphic : public Graphic {
public:
    HeroGraphic(Hero* explorer);

    void draw() override;
    void update(uint32_t dt) override;

private:
    tweeny::tween<int, int> m_current =
        tweeny::from(-1, -1).to(-1, -1).during(2000);
    Hero* m_pHero;
};