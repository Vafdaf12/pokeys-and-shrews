#pragma once

#include "core/GameObject.h"
#include "core/Graphic.h"
#include "lair/Lair.h"
#include "raylib.h"
#include "ui/Button.h"

#include <map>
#include <vector>

class TileEntity;

class EntityEditor : public Graphic, public GameObject {
public:
    EntityEditor(Font font) : GameObject(nullptr), m_font(font) {}

    void draw() override;
    void update(float dt) override;

    void addEntity(TileEntity* entity);

    inline TileEntity* getActive() { return m_pActive; }

    inline Rectangle getBoundingBox() const override {
        assert(false && "Not bounding box for entity editor");
        return {0, 0, 0, 0};
    }

private:
    Font m_font;

    TileEntity* m_pActive = nullptr;
    std::map<TileEntity*, ui::Button> m_available;
};