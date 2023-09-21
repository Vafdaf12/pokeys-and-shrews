#pragma once

#include "core/Graphic.h"
#include "lair/Lair.h"
#include "raylib.h"
#include "ui/Button.h"

#include <map>
#include <vector>

class TileEntity;

class EntityEditor : public Graphic {
public:
    EntityEditor(Font font) : m_font(font) {}

    void draw() override;
    void update(float dt) override;

    void addEntity(TileEntity* entity, const std::string& name);

    inline TileEntity* getActive() { return m_pActive; }

private:
    Font m_font;

    TileEntity* m_pActive = nullptr;
    std::map<TileEntity*, ui::Button> m_available;
};