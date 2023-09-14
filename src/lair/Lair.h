#pragma once

#include "lair/LairExplorer.h"
#include "lair/Tile.h"

#include <vcruntime.h>
#include <vector>

class Lair {
public:
    friend class LairGraphic;
    enum ExploreType {
        DEPTH_FIRST,
        BREADTH_FIRST,
    };
    Lair(size_t w, size_t h);

    bool removeTile(int x, int y);
    Tile* addTile(int x, int y);
    Tile* getTile(int x, int y);

    LairExplorer* createExplorer(ExploreType type) const;

private:
    size_t index(int x, int y) const;
    size_t m_width, m_height;
    std::vector<Tile*> m_tiles;
};