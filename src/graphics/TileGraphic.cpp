#include "TileGraphic.h"
#include "lair/Tile.h"

#include "SDL_render.h"

#include <cassert>
#include <vector>

TileGraphic::TileGraphic(const Tile* tile, int x, int y)
    : m_position({x, y}), m_tile(tile) {
    assert(tile);
}

void TileGraphic::draw(TargetType target) const {
    SDL_Rect rect = {m_position.x, m_position.y, TILE_WIDTH, TILE_WIDTH};

    if (m_tile->m_fortified) {
        SDL_SetRenderDrawColor(target, 0xaa, 0xee, 0xaa, 255);
    } else {
        SDL_SetRenderDrawColor(target, 0xee, 0xee, 0xee, 255);
    }
    SDL_RenderFillRect(target, &rect);

    SDL_SetRenderDrawColor(target, 0, 0, 0, 255);
    auto [x, y] = m_position;

    if (!m_tile->north) {
        SDL_RenderDrawLine(target, x, y, x + TILE_WIDTH, y);
    }
    if (!m_tile->south) {
        SDL_RenderDrawLine(
            target, x, y + TILE_WIDTH, x + TILE_WIDTH, y + TILE_WIDTH);
    }
    if (!m_tile->west) {
        SDL_RenderDrawLine(target, x, y, x, y + TILE_WIDTH);
    }
    if (!m_tile->east) {
        SDL_RenderDrawLine(
            target, x + TILE_WIDTH, y, x + TILE_WIDTH, y + TILE_WIDTH);
    }
}