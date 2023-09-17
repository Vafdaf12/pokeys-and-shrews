#pragma once

#include "trap/Trap.h"

class Tile {
public:
    inline Tile(int x, int y) : x(x), y(y) {}

    enum Direction { North, West, East, South };

    void setNeighbour(Tile* tile, Direction dir);
    Tile* getNeighbour(Direction dir);

    friend class TileGraphic;

    inline void fortify() { m_fortified = true; }
    inline int getX() const { return x; }
    inline int getY() const { return y; }

    inline void addTrap(Trap* trap) { m_pTrap = trap; }
    inline Trap* getTrap() { return m_pTrap; }

private:
    int x, y;
    bool m_fortified = false;
    Tile* west = nullptr;
    Tile* east = nullptr;
    Tile* north = nullptr;
    Tile* south = nullptr;

    Trap* m_pTrap = nullptr;
};