#include "LairExplorerGraphic.h"
#include "SDL_blendmode.h"
#include "SDL_render.h"
#include "graphics/TileGraphic.h"
#include "lair/LairExplorer.h"

LairExplorerGraphic::LairExplorerGraphic(LairExplorer* explorer)
    : m_pExplorer(explorer) {
    m_color.r = rand() % 255;
    m_color.g = rand() % 255;
    m_color.b = rand() % 255;
}
void LairExplorerGraphic::draw(TargetType target) const {
    Tile* tile = m_pExplorer->get();
    if (!tile) return;

    int x = tile->getX() * TileGraphic::TILE_WIDTH + 20;
    int y = tile->getY() * TileGraphic::TILE_WIDTH + 20;
    SDL_Rect rect = {x, y, TileGraphic::TILE_WIDTH, TileGraphic::TILE_WIDTH};

    SDL_SetRenderDrawBlendMode(target, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(target, 255, 0, 0, 100);
    SDL_RenderFillRect(target, &rect);

    SDL_SetRenderDrawColor(target, m_color.r, m_color.g, m_color.b, 255);
    SDL_RenderDrawLines(target, m_points.data(), m_points.size());
}

void LairExplorerGraphic::update() {
    Tile* tile = m_pExplorer->get();
    if (!tile) return;

    SDL_Point p = {20 + tile->getX() * TileGraphic::TILE_WIDTH +
                       (TileGraphic::TILE_WIDTH / 2),
        20 + tile->getY() * TileGraphic::TILE_WIDTH +
            (TileGraphic::TILE_WIDTH / 2)};

    if (m_points.empty()) {
        m_points.push_back(p);
        return;
    }
    if (m_points.back().x == p.x && m_points.back().y == p.y) return;

    m_points.push_back(p);
}