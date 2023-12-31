#include "HeroGraphic.h"

#include "core/Engine.h"
#include "core/Resources.h"
#include "core/UserInterface.h"
#include "editor/LairEditor.h"
#include "lair/BreadthFirstExplorer.h"
#include "lair/DepthFirstExplorer.h"
#include "raylib.h"
#include "tween.h"
#include "tweeny.h"

#include "graphics/TileGraphic.h"
#include "hero/Hero.h"
#include "util/util.h"

#include <algorithm>
#include <iostream>
#include <stdio.h>

HeroGraphic::HeroGraphic(const Hero* hero) : m_pHero(hero) {
    if (dynamic_cast<DepthFirstExplorer*>(m_pHero->m_pExplorer)) {
        m_texture = Resources::getTexture("res/eduardo.png");
        m_textureStunned = Resources::getTexture("res/eduardo_stunned.png");
    } else if (dynamic_cast<BreadthFirstExplorer*>(m_pHero->m_pExplorer)) {
        m_texture = Resources::getTexture("res/Hero1.png");
        m_textureStunned = Resources::getTexture("res/Hero1_stunned.png");
    }
}
Color getHealthColor(float fac) {

    float facR = std::clamp((1 - fac) * 2, 0.f, 1.f);
    float facG = std::clamp(fac * 2, 0.f, 1.f);
    uint8_t r = uint8_t(facR * 255);
    uint8_t g = uint8_t(facG * 255);

    return {r, g, 0, 255};
}
void HeroGraphic::draw() {
    auto [x, y] = m_current.peek();

    float fac = (float)m_pHero->m_remainingHealth / m_pHero->m_totalHealth;
    float scale = TileGraphic::TILE_WIDTH / float(m_texture.width);

    Color c = getHealthColor(fac);
    Vector2 p{static_cast<float>(x), static_cast<float>(y)};
    if (!m_pHero->m_stunTimer.isComplete()) {
        DrawTextureEx(m_textureStunned, p, 0, scale, WHITE);
    } else {

        DrawTextureEx(m_texture, p, 0, scale, WHITE);
    }

    util::drawProgress(
        {p.x, p.y, TileGraphic::TILE_WIDTH, TileGraphic::TILE_WIDTH},
        4,
        4,
        fac,
        c);
}
void HeroGraphic::update(float dt) {
    Tile* tile = m_pHero->getExplorer()->get();

    int x = LairEditor::MAP_OFFSET.x + tile->getX() * TileGraphic::TILE_WIDTH;
    int y = LairEditor::MAP_OFFSET.y + tile->getY() * TileGraphic::TILE_WIDTH;
    auto [cx, cy] = m_current.peek();
    auto [tx, ty] = m_current.peek(1.f);

    if (tx == -1 || ty == -1) {
        m_current = tweeny::from(x, y).to(x, y);
    } else if (tx != x || ty != y) {
        m_current = tweeny::from(cx, cy).to(x, y).during(100);
    }

    m_current.step(dt / 0.1f);
}
Rectangle HeroGraphic::getBoundingBox() const {
    return {m_position.x,
        m_position.y,
        TileGraphic::TILE_WIDTH,
        TileGraphic::TILE_WIDTH};
}