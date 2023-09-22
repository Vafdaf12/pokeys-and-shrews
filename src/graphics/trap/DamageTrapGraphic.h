#pragma once

#include "core/Graphic.h"
#include "raylib.h"

class DamageTrap;

class DamageTrapGraphic : public Graphic {
public:
    DamageTrapGraphic(const DamageTrap* trap);
    void draw() override;
    Rectangle getBoundingBox() const override;

private:
    Texture2D m_texture;
    const DamageTrap* m_pTrap;
};