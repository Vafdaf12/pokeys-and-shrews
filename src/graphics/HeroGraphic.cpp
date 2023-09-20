#include "HeroGraphic.h"

#include "raylib.h"
#include "tween.h"
#include "tweeny.h"

#include "graphics/TileGraphic.h"
#include "hero/Hero.h"

#include <algorithm>
#include <iostream>
#include <stdio.h>

HeroGraphic::HeroGraphic(Hero* hero) : m_pHero(hero) {}

void HeroGraphic::draw() {
    auto [x, y] = m_current.peek();

    float fac = (float)m_pHero->m_remainingHealth / m_pHero->m_totalHealth;
    float facR = std::clamp((1 - fac) * 2, 0.f, 1.f);
    float facG = std::clamp(fac * 2, 0.f, 1.f);

    uint8_t r = uint8_t(facR * 255);
    uint8_t g = uint8_t(facG * 255);

    Color c = {r, g, 0, 100};
    DrawRectangle(x, y, TileGraphic::TILE_WIDTH, TileGraphic::TILE_WIDTH, c);
}
void HeroGraphic::update(float dt) {
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

    m_current.step(dt * 1000);
}