#include "UserInterface.h"

#include "SDL_render.h"
#include "graphics/TileGraphic.h"
#include "lair/Tile.h"
#include <sstream>

void UserInterface::addTile(Tile* tile) {
    m_graphics[tile] = new TileGraphic(m_target,
        tile,
        tile->getX() * TileGraphic::TILE_WIDTH + 20,
        tile->getY() * TileGraphic::TILE_WIDTH + 20);
}
bool UserInterface::removeTile(Tile* tile) {
    auto it = m_graphics.find(tile);
    if (it == m_graphics.end()) return false;
    m_graphics.erase(it->first);
    return true;
}
void UserInterface::setBalance(int balance) {
    std::stringstream s;
    s << "$ " << balance;
    m_balance.setText(s.str());
}

void UserInterface::draw() const {
    SDL_SetRenderDrawColor(m_target, 0xff, 0xff, 0xff, 255);
    SDL_RenderClear(m_target);

    for (const auto& p : m_graphics) {
        p.second->draw();
    }

    m_balance.draw();
}