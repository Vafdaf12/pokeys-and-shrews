#include "LairExplorerGraphic.h"

#include "core/Engine.h"
#include "core/UserInterface.h"
#include "editor/LairEditor.h"
#include "graphics/TileGraphic.h"
#include "lair/LairExplorer.h"
#include "raylib.h"
#include <cmath>

LairExplorerGraphic::LairExplorerGraphic(LairExplorer* explorer)
    : m_pExplorer(explorer) {
    m_color.r = rand() % 255;
    m_color.g = rand() % 255;
    m_color.b = rand() % 255;
    m_color.a = 100;
    m_cur = LairEditor::MAP_OFFSET;
    m_cur.x += explorer->get()->getX() + int(TileGraphic::TILE_WIDTH / 2);
    m_cur.y += explorer->get()->getY() + int(TileGraphic::TILE_WIDTH / 2);
    m_position = m_cur;
}
void LairExplorerGraphic::draw() {
    Tile* tile = m_pExplorer->get();
    if (!tile) return;

    int x = m_cur.x - int(TileGraphic::TILE_WIDTH / 2);
    int y = m_cur.y - int(TileGraphic::TILE_WIDTH / 2);

    DrawRectangle(
        x, y, TileGraphic::TILE_WIDTH, TileGraphic::TILE_WIDTH, m_color);

    DrawLineStrip(m_points.data(),
        m_points.size(),
        {m_color.r, m_color.g, m_color.b, 255});
}

void LairExplorerGraphic::update(float dt) {
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

    Vector2 p = LairEditor::MAP_OFFSET;
    p.x += tile->getX() * TileGraphic::TILE_WIDTH +
           float(TileGraphic::TILE_WIDTH) / 2;

    p.y += tile->getY() * TileGraphic::TILE_WIDTH +
           float(TileGraphic::TILE_WIDTH) / 2;

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
Rectangle LairExplorerGraphic::getBoundingBox() const {
    return {m_position.x,
        m_position.y,
        TileGraphic::TILE_WIDTH,
        TileGraphic::TILE_WIDTH};
}