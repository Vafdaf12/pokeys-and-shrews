#include "Storyteller.h"
#include "hero/Hero.h"
#include "lair/BreadthFirstExplorer.h"
#include "lair/DepthFirstExplorer.h"

#include <iterator>
#include <list>
#include <stdlib.h>

void Storyteller::addSpawnTile(Tile* tile) { m_spawnTiles.push_back(tile); }
bool Storyteller::removeSpawnTile(Tile* tile) {
    return std::erase(m_spawnTiles, tile) > 0;
}

Hero* Storyteller::spawnHero() {
    size_t i = static_cast<size_t>(rand()) % m_spawnTiles.size();
    auto it = m_spawnTiles.begin();
    std::advance(it, i);

    Hero* hero = new Hero(new BreadthFirstExplorer(*it), 10, 1, 10, m_pEngine);
    m_pHeroes.emplace_back(hero);
    if (m_pEngine) m_pEngine->heroSpawned(hero);

    return hero;
}
void Storyteller::update(uint32_t dt) {
    m_spawnTimer.update(dt);
    if (m_spawnTimer.isComplete()) {
        m_spawnTimer.tick();
        spawnHero();
    }
    for (Hero* h : m_pHeroes) {
        h->update(dt);
    }
}
