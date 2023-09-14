#pragma once

#include "lair/Tile.h"

class LairExplorer {
public:
    /// @return the entrance of the lair to start exploring from
    virtual Tile* entrance() const = 0;

    /// @return The destination room to find by exploration
    virtual Tile* destination() const = 0;

    /// Go to the next room
    virtual void next() = 0;

    /// Retrieves the current room
    virtual operator Tile*() const = 0;
};