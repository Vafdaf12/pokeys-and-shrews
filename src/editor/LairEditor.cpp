#include "LairEditor.h"

#include "entity/TileEntity.h"
#include "graphics/TileGraphic.h"
#include <stdio.h>

void LairEditor::draw() {
    for (auto& [t, g] : m_tiles) {
        g->draw();
    }
    for (const auto& [t, g] : m_tileEntities) {
        g->draw();
    }
}
void LairEditor::update(float dt) {
    for (auto& [t, g] : m_tiles) {
        g->update(dt);
    }
    for (const auto& [t, g] : m_tileEntities) {
        g->update(dt);
    }

    Vector2 p = getWorldSpacePosition(GetMousePosition());
    int x = static_cast<int>(p.x);
    int y = static_cast<int>(p.y);

    Tile* tile = m_pLair->getTile(x, y);

    // TODO: this some ugly hack fr fr. memory allocation go brrrrr
    bool free = tile == nullptr;
    if (!tile) tile = new Tile(x, y);

    switch (getAction()) {
    case EditAction::Fortify: m_pEngine->tileFortified(this, tile); break;
    case EditAction::AddTile: m_pEngine->tileAdded(this, tile); break;
    case EditAction::RemoveTile: m_pEngine->tileRemoved(this, tile); break;
    case EditAction::RemoveEntity:
        m_pEngine->tileEntityRemoved(this, tile, tile->getEntity());
        break;
    case EditAction::AddEntity:
        m_pEngine->tileEntityAdded(this, tile, nullptr);
        break;
    default: break;
    }
    if (free) delete tile;
}
void LairEditor::addTileEntity(const Tile& tile, const TileEntity& entity) {
    assert(m_tiles.find(&tile) != m_tiles.end());

    Vector2 pos = m_tiles[&tile]->getPosition();

    std::unique_ptr<Graphic> graphic(entity.createGraphic());
    graphic->setPosition(pos);
    m_tileEntities[&entity] = std::move(graphic);
}
bool LairEditor::removeTileEntity(const TileEntity& entity) {
    if (m_tileEntities.find(&entity) == m_tileEntities.end()) return false;
    m_tileEntities.erase(&entity);
    return true;
}
void LairEditor::addTile(const Tile& tile) {
    m_tiles[&tile] = std::make_unique<TileGraphic>(&tile,
        tile.getX() * TileGraphic::TILE_WIDTH + MAP_OFFSET.x,
        tile.getY() * TileGraphic::TILE_WIDTH + MAP_OFFSET.y);
}
bool LairEditor::removeTile(const Tile& tile) {
    if (m_tiles.find(&tile) == m_tiles.end()) return false;
    m_tiles.erase(&tile);
    return true;
}
LairEditor::EditAction LairEditor::getAction() const {
    Vector2 p = getWorldSpacePosition(GetMousePosition());
    if (p.x < 0 || p.y < 0) return EditAction::None;

    int x = static_cast<int>(p.x);
    int y = static_cast<int>(p.y);

    Tile* tile = m_pLair->getTile(x, y);

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (!tile) return EditAction::AddTile;
        if (!tile->isFortified()) return EditAction::Fortify;
        if (!tile->getEntity()) return EditAction::AddEntity;
    }
    if (!tile) return EditAction::None;
    Tile::BakeLevel lvl = tile->getBakeLevel();
    if (lvl > Tile::FIXED) return EditAction::None;

    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
        if (!tile->isFortified()) return EditAction::RemoveTile;
        if (tile->getEntity()) return EditAction::RemoveEntity;
    }
    return EditAction::None;
}
Vector2 LairEditor::getWorldSpacePosition(Vector2 pos) const {
    pos.x = (pos.x - MAP_OFFSET.x) / TileGraphic::TILE_WIDTH;
    pos.y = (pos.y - MAP_OFFSET.y) / TileGraphic::TILE_WIDTH;

    return pos;
}