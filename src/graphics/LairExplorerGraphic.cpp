#include "LairExplorerGraphic.h"
#include "SDL_blendmode.h"
#include "SDL_render.h"
#include "graphics/TileGraphic.h"
#include "lair/LairExplorer.h"
#include <cmath>

LairExplorerGraphic::LairExplorerGraphic(LairExplorer* explorer)
    : m_pExplorer(explorer) {
    m_color.r = rand() % 255;
    m_color.g = rand() % 255;
    m_color.b = rand() % 255;
    m_cur.x = explorer->get()->getX() + 20 + TileGraphic::TILE_WIDTH / 2;
    m_cur.y = explorer->get()->getY() + 20 + TileGraphic::TILE_WIDTH / 2;
    m_dest = m_cur;
}
void LairExplorerGraphic::draw(TargetType target) const {
    Tile* tile = m_pExplorer->get();
    if (!tile) return;

    int x = m_cur.x - TileGraphic::TILE_WIDTH / 2;
    int y = m_cur.y - TileGraphic::TILE_WIDTH / 2;

    SDL_Rect rect = {x, y, TileGraphic::TILE_WIDTH, TileGraphic::TILE_WIDTH};

    SDL_SetRenderDrawBlendMode(target, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(target, m_color.r, m_color.g, m_color.b, 100);
    SDL_RenderFillRect(target, &rect);

    SDL_SetRenderDrawColor(target, m_color.r, m_color.g, m_color.b, 255);
    SDL_RenderDrawLines(target, m_points.data(), m_points.size());
}

void LairExplorerGraphic::update(uint32_t dt) {
    m_cur.x += std::round((m_dest.x - m_cur.x) / 4.0f);
    m_cur.y += std::round((m_dest.y - m_cur.y) / 4.0f);
    if (std::abs(m_cur.x - m_dest.x) < 5) {
        m_cur.x = m_dest.x;
    }
    if (std::abs(m_cur.y - m_dest.y) < 5) {
        m_cur.y = m_dest.y;
    }
    Tile* tile = m_pExplorer->get();
    if (!tile) return;

    SDL_Point p = {20 + tile->getX() * TileGraphic::TILE_WIDTH +
                       (TileGraphic::TILE_WIDTH / 2),
        20 + tile->getY() * TileGraphic::TILE_WIDTH +
            (TileGraphic::TILE_WIDTH / 2)};

    if (m_points.empty()) {
        m_points.push_back(p);
        m_dest = m_points.back();
        return;
    }
    if (m_points.back().x == p.x && m_points.back().y == p.y) return;

    m_points.push_back(p);
    if (m_points.size() > 5) {
        for (size_t i = 0; i < m_points.size() - 1; i++) {
            m_points[i] = m_points[i + 1];
        }
        m_points.pop_back();
    }
    m_dest = m_points.back();
}