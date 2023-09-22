#pragma once

#include "core/GameObject.h"
#include "core/Timer.h"
#include <vector>

class Tile;
class Engine;
class Hero;

class Storyteller : public GameObject {
public:
    inline Storyteller(uint32_t required, Engine* engine = nullptr)
        : GameObject(engine), m_required(required) {}

    void addSpawnTile(Tile* tile);
    bool removeSpawnTile(Tile* tile);

    void update(float dt);

    Hero* spawnHero();
    void killHero(Hero* hero);

    void nextWave(uint32_t required);

    void reset();

private:
    uint32_t m_required;
    uint32_t m_current = 0;
    Timer m_spawnTimer = Timer(3);
    std::vector<Tile*> m_spawnTiles;
    std::vector<Hero*> m_heroes;
};