#include "EntityEditor.h"

#include "core/Resources.h"
#include "graphics/TileGraphic.h"
#include "raylib.h"
#include <algorithm>

#include "entity/TileEntity.h"
#include "render/Drawable.h"
#include "render/Frame.h"
#include "ui/Button.h"
#include "util/util.h"

void EntityEditor::draw() {
    for (auto& [e, btn] : m_available) {
        btn->draw();
    }
}
void EntityEditor::update(float dt) {
    for (auto& [e, btn] : m_available) {
        btn->update(dt);
    }
}

void EntityEditor::setActive(const TileEntity* active) {
    if (active == m_pActive) return;

    // Add new decorated frame
    if (!m_pActive) {
        gfx::Drawable* g = m_available[active];
        const static float p = 4;
        const static Texture2D tex =
            Resources::getTexture("res/frame_small.png");

        float s = TileGraphic::TILE_WIDTH;
        m_available[active] = new gfx::Frame(
            tex, std::unique_ptr<gfx::Drawable>(g), p, s, gfx::Frame::Fg);
    }

    // Remove frame
    else if (!active) {
        gfx::Frame* f = (gfx::Frame*)(m_available[m_pActive]);
        m_available[m_pActive] = f->unwrap();
        delete f;
    }
    // Move frames
    else {
        setActive(nullptr);
        setActive(active);
    }

    m_pActive = active;
}
void EntityEditor::addEntity(const TileEntity* entity) {
    assert(entity);

    float y = m_position.y;
    for (const auto& [e, btn] : m_available) {
        y += btn->getBoundingBox().height + 5;
    }
    ui::Button* btn =
        new ui::Button(std::unique_ptr<gfx::Drawable>(entity->createGraphic()),
            [=]() { setActive(this->m_pActive == entity ? nullptr : entity); });
    btn->getInternal<gfx::Graphic>()->setPosition({m_position.x, y});
    m_available.emplace(entity, btn);
}