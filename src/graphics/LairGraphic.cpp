#include "LairGraphic.h"

#include "SDL_rect.h"
#include "SDL_render.h"
#include "graphics/TileGraphic.h"
#include "lair/Lair.h"

void LairGraphic::draw(TargetType target) const {
    for (size_t y = 0; y < m_lair->m_height; y++) {
        for (size_t x = 0; x < m_lair->m_width; x++) {
            Tile* tile = m_lair->getTile(x, y);
            if (!tile) continue;

            SDL_Point p = START_POINT;
            p.x += x * TileGraphic::TILE_WIDTH;
            p.y += y * TileGraphic::TILE_WIDTH;
            TileGraphic(tile, p.x, p.y).draw(target);
        }
    }
}