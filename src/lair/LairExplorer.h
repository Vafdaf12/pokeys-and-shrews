#pragma once

#include "lair/Tile.h"
#include <stdint.h>

class LairExplorer {
public:
    /**
     * Sets the starting point of the exploration, resetting any exploration
     * that has been done
     * @param tile The new tile to start from
     */
    virtual void setStart(Tile* tile) = 0;

    /// @return The starting point of exploration
    virtual Tile* getStart() const = 0;

    /**
     * Backtracks through the explored path through n steps
     * @param n The number of steps to backtrack
     */
    virtual void backtrack(uint32_t n = 1) = 0;

    /// Explore the next tile
    virtual void next() = 0;

    /// Retrieve the current tile
    virtual Tile* get() const = 0;
};