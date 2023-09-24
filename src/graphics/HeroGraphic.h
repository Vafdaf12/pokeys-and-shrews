#pragma once

#include "raylib.h"
#include "render/Drawable.h"
#include "tweeny.h"

class Hero;

class HeroGraphic : public gfx::Graphic {
public:
    HeroGraphic(const Hero* explorer);

    void draw() override;
    void update(float dt) override;

    Rectangle getBoundingBox() const override;

private:
    Texture2D m_texture;
    Texture2D m_textureStunned;
    tweeny::tween<int, int> m_current =
        tweeny::from(-1, -1).to(-1, -1).during(2000);
    const Hero* m_pHero;
};