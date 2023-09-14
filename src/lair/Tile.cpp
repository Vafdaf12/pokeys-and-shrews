#include "Tile.h"

void Tile::setNeighbour(Tile* tile, Direction dir) {
    switch (dir) {
    case North: north = tile; break;
    case West: west = tile; break;
    case East: east = tile; break;
    case South: south = tile; break;
    }
    if (!tile) return;

    switch (dir) {
    case North: tile->south = this; break;
    case West: tile->east = this; break;
    case East: tile->west = this; break;
    case South: tile->north = this; break;
    }
}
Tile* Tile::getNeighbour(Direction dir) {
    switch (dir) {
    case North: return north;
    case West: return west;
    case East: return south;
    case South: return east;
    }
}