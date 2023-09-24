#pragma once

class TileEntity;

class Tile {
public:
    inline Tile(int x, int y) : x(x), y(y) {}

    enum Direction { North, West, East, South };
    enum BakeLevel {
        // Both tile and its entity can be modified
        DYNAMIC = 0,

        // Only the entity can be modified
        FIXED = 1,

        // The tile cannot be modified in any way
        STATIC = 2,
    };

    void setNeighbour(Tile* tile, Direction dir);
    Tile* getNeighbour(Direction dir);

    friend class TileGraphic;

    inline void fortify() { m_fortified = true; }
    inline int getX() const { return x; }
    inline int getY() const { return y; }

    inline void setEntity(TileEntity* trap) { m_pEntity = trap; }
    inline TileEntity* getEntity() { return m_pEntity; }
    inline bool isFortified() const { return m_fortified; }

    inline BakeLevel getBakeLevel() const { return m_bakeLevel; }
    inline void bake(BakeLevel lvl) { m_bakeLevel = lvl; }

    char toString() const;

private:
    int x, y;
    bool m_fortified = false;
    BakeLevel m_bakeLevel = DYNAMIC;
    Tile* west = nullptr;
    Tile* east = nullptr;
    Tile* north = nullptr;
    Tile* south = nullptr;

    TileEntity* m_pEntity = nullptr;
};