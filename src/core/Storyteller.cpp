#include "Storyteller.h"
#include "core/Storyteller.h"
#include "hero/Hero.h"
#include "lair/BreadthFirstExplorer.h"
#include "lair/DepthFirstExplorer.h"

#include <algorithm>
#include <iterator>
#include <list>
#include <stdlib.h>

void Storyteller::addSpawnTile(Tile* tile) { m_spawnTiles.push_back(tile); }
bool Storyteller::removeSpawnTile(Tile* tile) {
    return std::erase(m_spawnTiles, tile) > 0;
}

Hero* Storyteller::spawnHero() {
    if (m_spawnTiles.size() == 0) return nullptr;
    size_t i = static_cast<size_t>(rand()) % m_spawnTiles.size();
    auto it = m_spawnTiles.begin();
    std::advance(it, i);

    Hero* hero = new Hero(createExplorer(*it), 10, 1, 10, m_pEngine);
    m_heroes.push_back(hero);

    if (m_pEngine) m_pEngine->heroSpawned(this, hero);
    return hero;
}
void Storyteller::killHero(Hero* hero) {
    auto it = std::find(m_heroes.begin(), m_heroes.end(), hero);
    if (m_pEngine) m_pEngine->heroDied(this, hero);
    delete *it;
    m_heroes.erase(it);

    m_current++;
    if (m_pEngine) {
        if (m_current < m_required)
            m_pEngine->waveProgressed(m_required, m_current);
        else m_pEngine->waveCompleted(this);
    }
}
void Storyteller::update(float dt) {
    if (!m_paused) {
        m_spawnTimer.update(dt);
    }
    if (m_spawnTimer.isComplete()) {
        m_spawnTimer.tick();
        spawnHero();
    }
    if (m_heroes.empty()) return;
    for (auto& h : m_heroes) {
        h->update(dt);
    }
}
void Storyteller::reset() {
    m_current = 0;
    for (auto& h : m_heroes) {
        if (m_pEngine) m_pEngine->heroDied(this, h);
    }
    m_heroes.clear();
    m_spawnTimer.reset();
    if (m_pEngine) m_pEngine->waveProgressed(m_required, 0);
}

void Storyteller::nextWave() {
    m_currentWave++;
    m_required += 2;
    if (m_currentWave >= m_totalWaves) {
        if (m_pEngine) m_pEngine->gameWon(this);
        return;
    }
    if (m_pEngine) m_pEngine->waveProgressed(m_required, 0);
}
bool Storyteller::isHeroOnTile(const Tile* tile) const {
    for (auto& h : m_heroes) {
        if (h->getExplorer()->get() == tile) return true;
    }
    return false;
}

LairExplorer* Storyteller::createExplorer(Tile* start) {
    int type = rand() % 2;
    switch (type) {
    case 0: return new DepthFirstExplorer(start);
    case 1: return new BreadthFirstExplorer(start);
    }
    return nullptr;
}