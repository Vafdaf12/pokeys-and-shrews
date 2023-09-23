#pragma once

#include "raylib.h"
#include "render/Drawable.h"

class Tile;

class TileGraphic : public gfx::Graphic {
public:
    TileGraphic(const Tile* tile, int x = 0, int y = 0);

    void draw() override;

    Rectangle getBoundingBox() const override;

    static constexpr int TILE_WIDTH = 50;

private:
    const Tile* m_tile;
};