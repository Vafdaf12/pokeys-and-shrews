#pragma once

#include "core/GameObject.h"
#include "lair/LairExplorer.h"
#include "lair/Tile.h"

#include <memory>
#include <string>
#include <vector>

class Engine;

class Lair : public GameObject {
public:
    friend class LairGraphic;
    Lair(size_t w, size_t h, Engine* pEngine = nullptr);

    bool removeTile(int x, int y);
    bool fortifyTile(int x, int y);
    Tile* addTile(int x, int y);
    Tile* getTile(int x, int y);

    void update(float dt);

    bool addEntity(int x, int y, TileEntity* entity);
    bool removeEntity(int x, int y);

    inline size_t getWidth() const { return m_width; }
    inline size_t getHeight() const { return m_height; }

    void reset();
    std::string toString() const;

private:
    size_t index(int x, int y) const;
    size_t m_width, m_height;
    std::vector<std::unique_ptr<Tile>> m_tiles;
};