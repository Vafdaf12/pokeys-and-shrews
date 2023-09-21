#pragma once

#include "core/Timer.h"
#include <list>

class Tile;
class Engine;
class Hero;

class Storyteller {
public:
    inline void setEngine(Engine* pEngine) { m_pEngine = pEngine; }

    void addSpawnTile(Tile* tile);
    bool removeSpawnTile(Tile* tile);

    void update(float dt);

    Hero* spawnHero();

private:
    Timer m_spawnTimer = Timer(3);
    Engine* m_pEngine = nullptr;
    std::list<Tile*> m_spawnTiles;
    std::list<Hero*> m_pHeroes;
};