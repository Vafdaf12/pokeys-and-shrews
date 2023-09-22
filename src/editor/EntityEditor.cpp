#include "EntityEditor.h"

#include "raylib.h"
#include <algorithm>

#include "entity/TileEntity.h"
#include "ui/Button.h"


Rectangle inset(const Rectangle& r, float insets) {
    return {
        r.x - insets,
        r.y - insets,
        r.width + 2 * insets,
        r.height + 2 * insets,
    };
}
void EntityEditor::draw() {
    for (auto& [e, btn] : m_available) {
        btn.draw();

        if (e == m_pActive) {
            Rectangle rect = inset(btn.getGraphic()->getBoundingBox(), 2);
            DrawRectangleLinesEx(rect, 1, RED);
        }
    }
}
void EntityEditor::update(float dt) {
    for (auto& [e, btn] : m_available) {
        btn.update(dt);
    }
}

void EntityEditor::addEntity(TileEntity* entity, const std::string& text) {
    assert(entity);

    float y = m_position.y;
    for (const auto& [e, btn] : m_available) {
        Graphic* g = btn.getGraphic();
        y += g->getBoundingBox().height + 5;
    }
    ui::Button btn(
        entity->createGraphic(), [=]() { this->m_pActive = entity; });
    btn.getGraphic()->setPosition({m_position.x, y});
    m_available.emplace(entity, std::move(btn));
}