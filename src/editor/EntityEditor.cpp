#include "EntityEditor.h"

#include "raylib.h"
#include <algorithm>

#include "entity/TileEntity.h"
#include "ui/Button.h"
#include "util/util.h"

void EntityEditor::draw() {
    for (auto& [e, btn] : m_available) {
        btn.draw();

        if (e == m_pActive) {
            Rectangle rect =
                util::inset(btn.getInternal()->getBoundingBox(), 2);
            DrawRectangleLinesEx(rect, 1, RED);
        }
    }
}
void EntityEditor::update(float dt) {
    for (auto& [e, btn] : m_available) {
        btn.update(dt);
    }
}

void EntityEditor::addEntity(TileEntity* entity) {
    assert(entity);

    float y = m_position.y;
    for (const auto& [e, btn] : m_available) {
        gfx::Graphic* g = btn.getInternal<gfx::Graphic>();
        y += g->getBoundingBox().height + 5;
    }
    ui::Button btn(
        std::unique_ptr<gfx::Drawable>(entity->createGraphic()), [=]() {
            this->m_pActive = this->m_pActive == entity ? nullptr : entity;
        });
    btn.getInternal<gfx::Graphic>()->setPosition({m_position.x, y});

    m_available.emplace(entity, std::move(btn));
}