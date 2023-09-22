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
    return nullptr;
}
char Tile::toString() const {
    int code = 0;
    if (north) code += 1;
    if (east) code += 2;
    if (south) code += 4;
    if (west) code += 8;

    static const char MAPPING[] = {
        '*', // ____
        // char(223), // N___
        char(179),
        // char(222), // _E__
        char(196),
        char(192), // NE__
        // char(220), // __S_
        char(179),
        char(179), // N_S_
        char(218), // _ES_
        char(195), // NES_
        // char(221), // ___W
        char(196),
        char(217), // N__W
        char(196), // _E_W
        char(193), // NE_W
        char(191), // __SW
        char(180), // N_SW
        char(194), // _ESW
        char(197), // NESW
    };
    return MAPPING[code];
}