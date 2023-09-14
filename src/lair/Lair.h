#pragma once

#include "lair/LairExplorer.h"
#include "lair/Tile.h"

#include <vector>

class Lair {
public:
    enum ExploreType {
        DEPTH_FIRST,
        BREADTH_FIRST,
    };

    void removeTile(Tile* tile);
    void addTile(Tile* tile);

    LairExplorer* createExplorer(ExploreType type) const;

private:
    std::vector<Tile*> m_rooms;
};