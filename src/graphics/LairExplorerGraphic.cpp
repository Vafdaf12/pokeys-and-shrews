#include "LairExplorerGraphic.h"
#include "SDL_blendmode.h"
#include "SDL_render.h"
#include "graphics/TileGraphic.h"
#include "lair/LairExplorer.h"
#include <cmath>

LairExplorerGraphic::LairExplorerGraphic(
    TargetType target, LairExplorer* explorer)
    : Graphic(target), m_pExplorer(explorer) {
    m_color.r = rand() % 255;
    m_color.g = rand() % 255;
    m_color.b = rand() % 255;
    m_cur.x = explorer->get()->getX() + 20 + TileGraphic::TILE_WIDTH / 2;
    m_cur.y = explorer->get()->getY() + 20 + TileGraphic::TILE_WIDTH / 2;
    m_position = m_cur;
}
void LairExplorerGraphic::draw() const {
    Tile* tile = m_pExplorer->get();
    if (!tile) return;

    int x = m_cur.x - TileGraphic::TILE_WIDTH / 2;
    int y = m_cur.y - TileGraphic::TILE_WIDTH / 2;

    SDL_Rect rect = {x, y, TileGraphic::TILE_WIDTH, TileGraphic::TILE_WIDTH};

    SDL_SetRenderDrawBlendMode(m_target, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(m_target, m_color.r, m_color.g, m_color.b, 100);
    SDL_RenderFillRect(m_target, &rect);

    SDL_SetRenderDrawColor(m_target, m_color.r, m_color.g, m_color.b, 255);
    SDL_RenderDrawLines(m_target, m_points.data(), m_points.size());
}

void LairExplorerGraphic::update(uint32_t dt) {
    m_cur.x += static_cast<int>((m_position.x - m_cur.x) / 4.0f);
    m_cur.y += static_cast<int>((m_position.y - m_cur.y) / 4.0f);
    if (std::abs(m_cur.x - m_position.x) < 5) {
        m_cur.x = m_position.x;
    }
    if (std::abs(m_cur.y - m_position.y) < 5) {
        m_cur.y = m_position.y;
    }
    Tile* tile = m_pExplorer->get();
    if (!tile) return;

    SDL_Point p = {20 + tile->getX() * TileGraphic::TILE_WIDTH +
                       (TileGraphic::TILE_WIDTH / 2),
        20 + tile->getY() * TileGraphic::TILE_WIDTH +
            (TileGraphic::TILE_WIDTH / 2)};

    if (m_points.empty()) {
        m_points.push_back(p);
        m_position = m_points.back();
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
    m_position = m_points.back();
}