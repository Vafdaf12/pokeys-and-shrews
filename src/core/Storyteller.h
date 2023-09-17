#pragma once

#include <list>

class Tile;
class Engine;
class LairExplorer;

class Storyteller {
public:
    inline void setEngine(Engine* pEngine) { m_pEngine = pEngine; }

    void addSpawnTile(Tile* tile);
    bool removeSpawnTile(Tile* tile);

    LairExplorer* createExplorer();

private:
    Engine* m_pEngine = nullptr;
    std::list<Tile*> m_spawnTiles;
};