#pragma once

class TileEntity;

class Tile {
public:
    enum Direction { North, West, East, South };

    void setNeighbour(Tile* tile, Direction dir);
    Tile* getNeighbour(Direction dir);

    TileEntity* contents = nullptr;

    friend class TileGraphic;

private:
    Tile* west = nullptr;
    Tile* east = nullptr;
    Tile* north = nullptr;
    Tile* south = nullptr;
};