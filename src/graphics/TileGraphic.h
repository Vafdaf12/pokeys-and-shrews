#pragma once

#include "core/Graphic.h"
#include "raylib.h"

class Tile;

class TileGraphic : public Graphic {
public:
    TileGraphic(const Tile* tile, int x = 0, int y = 0);

    void draw() override;

    Rectangle getBoundingBox() const override;

    static constexpr int TILE_WIDTH = 50;

private:
    const Tile* m_tile;
};