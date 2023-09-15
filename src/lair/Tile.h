#pragma once

class TileEntity;

class Tile {
public:
    inline Tile(int x, int y) : x(x), y(y) {}

    enum Direction { North, West, East, South };

    void setNeighbour(Tile* tile, Direction dir);
    Tile* getNeighbour(Direction dir);

    TileEntity* contents = nullptr;

    friend class TileGraphic;

    inline int getX() const { return x; }
    inline int getY() const { return y; }

private:
    int x, y;
    Tile* west = nullptr;
    Tile* east = nullptr;
    Tile* north = nullptr;
    Tile* south = nullptr;
};