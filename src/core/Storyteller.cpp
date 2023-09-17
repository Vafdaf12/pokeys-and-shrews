#include "Storyteller.h"
#include "lair/DepthFirstExplorer.h"

#include <iterator>
#include <list>
#include <stdlib.h>

void Storyteller::addSpawnTile(Tile* tile) { m_spawnTiles.push_back(tile); }
bool Storyteller::removeSpawnTile(Tile* tile) {
    return std::erase(m_spawnTiles, tile) > 0;
}

LairExplorer* Storyteller::createExplorer() {
    size_t i = static_cast<size_t>(rand()) % m_spawnTiles.size();
    auto it = m_spawnTiles.begin();
    std::advance(it, i);

    return new DepthFirstExplorer(*it);
}