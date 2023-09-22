#pragma once

#include "core/Graphic.h"
#include "raylib.h"

class Bank;

class BankGraphic : public Graphic {
public:
    BankGraphic(const Bank* trap);
    void draw() override;

    Rectangle getBoundingBox() const override;

private:
    Texture2D m_texture;
    const Bank* m_pTrap;
};