#pragma once

#include "SDL_rect.h"
#include "core/Graphic.h"

class Tile;

class TileGraphic : public Graphic {
public:
    TileGraphic(TargetType target, const Tile* tile, int x = 0, int y = 0);

    void draw() const override;

    static constexpr int TILE_WIDTH = 50;

private:
    const Tile* m_tile;
};