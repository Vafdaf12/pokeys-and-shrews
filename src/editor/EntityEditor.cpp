#include "EntityEditor.h"
#include "raylib.h"
#include "ui/Button.h"
#include <algorithm>

void EntityEditor::draw() {
    for (auto& [e, btn] : m_available) {
        btn.draw();
    }
}
void EntityEditor::update(float dt) {
    for (auto& [e, btn] : m_available) {
        btn.update(dt);
        if (e == m_pActive) {
            btn.setBackground(BLACK);
            btn.setTextColor(WHITE);

        } else {
            btn.setBackground(RAYWHITE);
            btn.setTextColor(BLACK);
        }
    }
}

void EntityEditor::addEntity(TileEntity* entity, const std::string& text) {
    assert(entity);

    float y = m_position.y;
    for (const auto& [e, btn] : m_available) {
        y += btn.getBoundingBox().height + 5;
    }
    ui::Button btn(m_font, text, [=]() { this->m_pActive = entity; });
    btn.setPosition({m_position.x, y});
    m_available.emplace(entity, std::move(btn));
}