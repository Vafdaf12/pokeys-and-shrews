#include "UserInterface.h"

#include "SDL_render.h"
#include "graphics/TileGraphic.h"
#include "lair/Tile.h"

void UserInterface::addTile(Tile* tile) {
    m_graphics[tile] = new TileGraphic(tile,
        tile->getX() * TileGraphic::TILE_WIDTH + 20,
        tile->getY() * TileGraphic::TILE_WIDTH + 20);
}
bool UserInterface::removeTile(Tile* tile) {
    auto it = m_graphics.find(tile);
    if (it == m_graphics.end()) return false;
    m_graphics.erase(it->first);
    return true;
}

void UserInterface::draw(Graphic::TargetType target) const {
    SDL_SetRenderDrawColor(target, 0xff, 0xff, 0xff, 255);
    SDL_RenderClear(target);

    for (const auto& p : m_graphics) {
        p.second->draw(target);
    }
}