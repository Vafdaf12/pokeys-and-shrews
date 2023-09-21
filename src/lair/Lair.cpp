#include "Lair.h"
#include "core/Engine.h"

#include <cassert>

Lair::Lair(size_t w, size_t h, Engine* pEngine)
    : GameObject(pEngine), m_width(w), m_height(h), m_tiles(w * h, nullptr) {}

bool Lair::fortifyTile(int x, int y) {
    if (x < 0 || y < 0) return false;
    if (x >= m_width || y >= m_height) return false;
    size_t i = index(x, y);
    if (!m_tiles[i]) return false;
    m_tiles[i]->fortify();
    if (m_pEngine) m_pEngine->tileFortified(this, m_tiles[i]);
    return true;
}
bool Lair::removeTile(int x, int y) {
    if (x < 0 || y < 0) return false;
    if (x >= m_width || y >= m_height) return false;
    size_t i = index(x, y);
    if (!m_tiles[i]) return false;

    size_t n = index(x, y - 1);
    size_t s = index(x, y + 1);
    size_t w = index(x - 1, y);
    size_t e = index(x + 1, y);

    if (y > 0 && m_tiles[n]) {
        m_tiles[n]->setNeighbour(nullptr, Tile::South);
    }
    if (y < m_height - 1 && m_tiles[s]) {
        m_tiles[s]->setNeighbour(nullptr, Tile::North);
    }
    if (x > 0 && m_tiles[w]) {
        m_tiles[w]->setNeighbour(nullptr, Tile::East);
    }
    if (x < m_width - 1 && m_tiles[e]) {
        m_tiles[e]->setNeighbour(nullptr, Tile::West);
    }

    if (m_pEngine) m_pEngine->tileRemoved(this, m_tiles[i]);
    m_tiles[i] = nullptr;

    return true;
}
Tile* Lair::addTile(int x, int y) {
    if (x < 0 || y < 0) return nullptr;
    if (x >= m_width || y >= m_height) return nullptr;
    size_t i = index(x, y);
    if (m_tiles[i]) return m_tiles[i];

    m_tiles[i] = new Tile(x, y);

    if (y > 0) {
        m_tiles[i]->setNeighbour(m_tiles[index(x, y - 1)], Tile::North);
    }
    if (y < m_height - 1) {
        m_tiles[i]->setNeighbour(m_tiles[index(x, y + 1)], Tile::South);
    }
    if (x > 0) {
        m_tiles[i]->setNeighbour(m_tiles[index(x - 1, y)], Tile::West);
    }
    if (x < m_width - 1) {
        m_tiles[i]->setNeighbour(m_tiles[index(x + 1, y)], Tile::East);
    }
    if (m_pEngine) m_pEngine->tileAdded(this, m_tiles[i]);

    return m_tiles[i];
}
Tile* Lair::getTile(int x, int y) {
    if (x < 0 || y < 0) return nullptr;
    if (x >= m_width || y >= m_height) return nullptr;
    size_t i = index(x, y);
    return m_tiles[i];
}
bool Lair::addEntity(int x, int y, TileEntity* entity) {
    Tile* tile = getTile(x, y);
    if (!tile) return false;

    tile->setEntity(entity);
    if (m_pEngine) m_pEngine->tileEntityAdded(this, tile, entity);
    return true;
}
bool Lair::removeEntity(int x, int y) {
    Tile* tile = getTile(x, y);
    if (!tile) return false;
    if (tile->isBaked()) return false;

    TileEntity* entity = tile->getEntity();
    if (!entity) return false;
    tile->setEntity(nullptr);

    if (m_pEngine) m_pEngine->tileEntityRemoved(this, tile, entity);
    return true;
}

size_t Lair::index(int x, int y) const { return y * m_width + x; }