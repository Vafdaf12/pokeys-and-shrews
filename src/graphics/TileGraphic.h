#pragma once

#include "SDL_rect.h"
#include "core/Graphic.h"

class Tile;

class TileGraphic : public Graphic {
public:
    TileGraphic(const Tile* tile, int x = 0, int y = 0);

    void draw(TargetType target) const override;
    inline void setPosition(int x, int y) { m_position = {x, y}; }

    static constexpr int TILE_WIDTH = 50;

private:
    SDL_Point m_position;
    const Tile* m_tile;
};