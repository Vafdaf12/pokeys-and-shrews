#include "TileGraphic.h"
#include "lair/Tile.h"
#include "raylib.h"

#include <cassert>
#include <vector>

TileGraphic::TileGraphic(const Tile* tile, int x, int y) : m_tile(tile) {
    assert(tile);
    m_position = {static_cast<float>(x), static_cast<float>(y)};
}

void TileGraphic::draw() {
    Color c = {0xee, 0xee, 0xee, 0xff};

    if (m_tile->m_pEntity) {
        c = {0xee, 0xee, 0xaa, 0xff};
    } else if (m_tile->m_fortified) {
        c = {0xaa, 0xee, 0xaa, 255};
    } else {
        c = {0xee, 0xee, 0xee, 255};
    }
    DrawRectangle(m_position.x, m_position.y, TILE_WIDTH, TILE_WIDTH, c);

    c = {0, 0, 0, 255};
    auto [x, y] = m_position;

    if (!m_tile->north) {
        DrawLine(x, y, x + TILE_WIDTH, y, c);
    }
    if (!m_tile->south) {
        DrawLine(x, y + TILE_WIDTH, x + TILE_WIDTH, y + TILE_WIDTH, c);
    }
    if (!m_tile->west) {
        DrawLine(x, y, x, y + TILE_WIDTH, c);
    }
    if (!m_tile->east) {
        DrawLine(x + TILE_WIDTH, y, x + TILE_WIDTH, y + TILE_WIDTH, c);
    }
}