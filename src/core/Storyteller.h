#pragma once

#include "core/GameObject.h"
#include "core/Timer.h"
#include <list>

class Tile;
class Engine;
class Hero;

class Storyteller : public GameObject {
public:
    inline Storyteller(Engine* engine = nullptr) : GameObject(engine) {}

    void addSpawnTile(Tile* tile);
    bool removeSpawnTile(Tile* tile);

    void update(float dt);

    Hero* spawnHero();

private:
    Timer m_spawnTimer = Timer(3);
    std::list<Tile*> m_spawnTiles;
    std::list<Hero*> m_pHeroes;
};