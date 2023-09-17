#include "HeroGraphic.h"

#include "graphics/TileGraphic.h"
#include "hero/Hero.h"

#include "SDL_render.h"
#include <algorithm>

HeroGraphic::HeroGraphic(Hero* hero) : m_pHero(hero) {}

void HeroGraphic::draw(TargetType target) const {
    Tile* tile = m_pHero->getExplorer()->get();

    int x = 20 + tile->getX() * TileGraphic::TILE_WIDTH;
    int y = 20 + tile->getY() * TileGraphic::TILE_WIDTH;

    SDL_Rect rect = {x, y, TileGraphic::TILE_WIDTH, TileGraphic::TILE_WIDTH};

    float fac = (float)m_pHero->m_remainingHealth / m_pHero->m_totalHealth;
    float facR = std::clamp((1 - fac) * 2, 0.f, 1.f);
    float facG = std::clamp(fac * 2, 0.f, 1.f);

    int r = static_cast<int>(facR * 255);
    int g = static_cast<int>(facG * 255);

    SDL_SetRenderDrawBlendMode(target, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(target, r, g, 0, 100);
    SDL_RenderFillRect(target, &rect);
}