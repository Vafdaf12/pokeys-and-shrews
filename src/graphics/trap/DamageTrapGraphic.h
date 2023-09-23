#pragma once

#include "raylib.h"
#include "render/Drawable.h"

class DamageTrap;

class DamageTrapGraphic : public gfx::Graphic {
public:
    DamageTrapGraphic(const DamageTrap* trap);
    void draw() override;
    Rectangle getBoundingBox() const override;

private:
    Texture2D m_texture;
    const DamageTrap* m_pTrap;
};