#pragma once

#include "lair/LairExplorer.h"
#include "lair/Tile.h"

#include <vector>

class Engine;

class Lair {
public:
    friend class LairGraphic;
    enum ExploreType {
        DEPTH_FIRST,
        BREADTH_FIRST,
    };
    Lair(size_t w, size_t h, Engine* pEngine = nullptr);

    bool removeTile(int x, int y);
    Tile* addTile(int x, int y);
    Tile* getTile(int x, int y);

    LairExplorer* createExplorer(ExploreType type) const;

    inline void setEngine(Engine* e) { m_pEngine = e; }

    inline size_t getWidth() const { return m_width; }
    inline size_t getHeight() const { return m_height; }

private:
    Engine* m_pEngine;
    size_t index(int x, int y) const;
    size_t m_width, m_height;
    std::vector<Tile*> m_tiles;
};