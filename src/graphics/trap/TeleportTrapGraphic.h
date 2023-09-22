#pragma once

#include "core/Graphic.h"
#include "raylib.h"

class TeleportTrap;

class TeleportTrapGraphic : public Graphic {
public:
    TeleportTrapGraphic(const TeleportTrap* trap);
    void draw() override;

    Rectangle getBoundingBox() const override;

private:
    Texture2D m_texture;
    const TeleportTrap* m_pTrap;
};