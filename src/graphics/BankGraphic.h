#pragma once

#include "raylib.h"
#include "render/Drawable.h"

class Bank;

class BankGraphic : public gfx::Graphic {
public:
    BankGraphic(const Bank* trap);
    void draw() override;

    Rectangle getBoundingBox() const override;

private:
    Texture2D m_texture;
    const Bank* m_pTrap;
};