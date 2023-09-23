#pragma once

#include "raylib.h"
#include "render/Drawable.h"

class TeleportTrap;

class TeleportTrapGraphic : public gfx::Graphic {
public:
    TeleportTrapGraphic(const TeleportTrap* trap);
    void draw() override;

    Rectangle getBoundingBox() const override;

private:
    Texture2D m_texture;
    const TeleportTrap* m_pTrap;
};