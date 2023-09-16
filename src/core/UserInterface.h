#pragma once

#include "core/Graphic.h"
#include <map>

class Tile;

class UserInterface : public Graphic {
public:
    /// Adds a graphics a render a tile
    void addTile(Tile* tile);

    /// Removes the graphic corresponding the passed-in tile
    bool removeTile(Tile* tile);

    void draw(TargetType target) const override;

private:
    std::map<void*, Graphic*> m_graphics;
};