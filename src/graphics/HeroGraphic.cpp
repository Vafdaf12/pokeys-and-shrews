#include "HeroGraphic.h"

#include "tween.h"
#include "tweeny.h"

#include "graphics/TileGraphic.h"
#include "hero/Hero.h"

#include "SDL_render.h"
#include <algorithm>
#include <iostream>
#include <stdio.h>

HeroGraphic::HeroGraphic(TargetType target, Hero* hero)
    : Graphic(target), m_pHero(hero) {}

void HeroGraphic::draw() const {
    auto [x, y] = m_current.peek();

    SDL_Rect rect = {x, y, TileGraphic::TILE_WIDTH, TileGraphic::TILE_WIDTH};

    float fac = (float)m_pHero->m_remainingHealth / m_pHero->m_totalHealth;
    float facR = std::clamp((1 - fac) * 2, 0.f, 1.f);
    float facG = std::clamp(fac * 2, 0.f, 1.f);

    int r = static_cast<int>(facR * 255);
    int g = static_cast<int>(facG * 255);

    SDL_SetRenderDrawBlendMode(m_target, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(m_target, r, g, 0, 100);
    SDL_RenderFillRect(m_target, &rect);
}
void HeroGraphic::update(uint32_t dt) {
    Tile* tile = m_pHero->getExplorer()->get();

    int x = 20 + tile->getX() * TileGraphic::TILE_WIDTH;
    int y = 20 + tile->getY() * TileGraphic::TILE_WIDTH;
    auto [cx, cy] = m_current.peek();
    auto [tx, ty] = m_current.peek(1.f);

    if (tx == -1 || ty == -1) {
        m_current = tweeny::from(x, y).to(x, y);
    } else if (tx != x || ty != y) {
        m_current = tweeny::from(cx, cy).to(x, y).during(100);
    }

    m_current.step(dt);
}