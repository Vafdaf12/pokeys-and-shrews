#pragma once

#include "raylib.h"
#include "render/Drawable.h"

class StunTrap;

class StunTrapGraphic : public gfx::Graphic {
public:
    StunTrapGraphic(const StunTrap* trap);
    void draw() override;

    Rectangle getBoundingBox() const override;

private:
    Texture2D m_texture;
    const StunTrap* m_pTrap;
};