#pragma once

class TileEntity;

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

    inline void setEntity(TileEntity* trap) { m_pEntity = trap; }
    inline TileEntity* getEntity() { return m_pEntity; }
    inline bool isFortified() const { return m_fortified; }
    inline bool isBaked() const { return m_baked; }

    inline void bake() { m_baked = true; }

    char toString() const;

private:
    int x, y;
    bool m_fortified = false;
    bool m_baked = false;
    Tile* west = nullptr;
    Tile* east = nullptr;
    Tile* north = nullptr;
    Tile* south = nullptr;

    TileEntity* m_pEntity = nullptr;
};