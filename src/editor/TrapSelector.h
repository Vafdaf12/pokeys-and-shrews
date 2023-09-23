#pragma once

#include "core/GameObject.h"
#include "lair/Lair.h"
#include "raylib.h"
#include "render/Drawable.h"
#include "ui/Button.h"

#include <cassert>
#include <map>
#include <vector>

class TileEntity;

class TrapSelector : public gfx::Graphic {
public:
    TrapSelector(Font font) : m_font(font) {}

    void draw() override;
    void update(float dt) override;

    void addEntity(const TileEntity* entity);

    inline const TileEntity* getActive() { return m_pActive; }

    inline Rectangle getBoundingBox() const override {
        assert(false && "Not bounding box for entity editor");
        return {0, 0, 0, 0};
    }

private:
    static constexpr gfx::Vec2 OFFSET = {20, 390};
    static constexpr gfx::Vec2 WIDTH = {75, 75};

    void setActive(const TileEntity* active);
    void layout();

    Font m_font;

    const TileEntity* m_pActive = nullptr;
    std::map<const TileEntity*, gfx::Drawable*> m_available;
};