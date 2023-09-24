#pragma once

#include "core/GameObject.h"
#include "core/Timer.h"
#include "lair/LairExplorer.h"
#include <vector>

class Tile;
class Engine;
class Hero;

class Storyteller : public GameObject {
public:
    inline Storyteller(
        uint32_t required, uint32_t waves, Engine* engine = nullptr)
        : GameObject(engine), m_totalWaves(waves), m_required(required) {}

    void addSpawnTile(Tile* tile);
    bool removeSpawnTile(Tile* tile);

    void update(float dt);

    Hero* spawnHero();
    void killHero(Hero* hero);

    void nextWave();

    void reset();

    bool isHeroOnTile(const Tile* tile) const;

    inline void togglePause() { m_paused = !m_paused; }

private:
    LairExplorer* createExplorer(Tile* start);
    uint32_t m_currentWave = 0;
    uint32_t m_totalWaves;
    bool m_paused = false;

    uint32_t m_required;
    uint32_t m_current = 0;
    Timer m_spawnTimer = Timer(3);
    std::vector<Tile*> m_spawnTiles;
    std::vector<Hero*> m_heroes;
};