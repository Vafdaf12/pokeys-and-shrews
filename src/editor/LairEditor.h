#pragma once

#include "core/GameObject.h"
#include "core/Graphic.h"

#include <map>
#include <memory>

class Tile;
class TileEntity;
class Lair;

class LairEditor : public GameObject, public Graphic {
public:
    constexpr static Vector2 MAP_OFFSET = {200, 20};

    inline LairEditor(Lair* pLair, Engine* pEngine)
        : GameObject(pEngine), m_pLair(pLair) {}

    void draw() override;
    void update(float dt) override;

    /// Adds a graphic to render a tile
    void addTile(const Tile& tile);

    /// Adds a graphics to render a tile entity
    void addTileEntity(const Tile& tile, const TileEntity& entity);

    /// Removes the graphic corresponding the passed-in tile
    bool removeTile(const Tile& tile);

    /// Removes the graphic corresponding the passed-in tile entity
    bool removeTileEntity(const TileEntity& entity);

    inline Rectangle getBoundingBox() const override {
        assert(false && "No Bounding box for Tile editor");
        return {};
    }

    Vector2 getWorldSpacePosition(Vector2 pos) const;

private:
    enum class EditAction {
        None,
        Fortify,
        AddTile,
        RemoveTile,
        AddEntity,
        RemoveEntity
    };
    EditAction getAction() const;

    Lair* m_pLair;
    std::map<const Tile*, std::unique_ptr<Graphic>> m_tiles;
    std::map<const TileEntity*, std::unique_ptr<Graphic>> m_tileEntities;
};