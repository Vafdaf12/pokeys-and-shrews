#include "TrapSelector.h"

#include "core/Resources.h"
#include "graphics/TileGraphic.h"
#include "raylib.h"
#include <algorithm>

#include "entity/TileEntity.h"
#include "render/Drawable.h"
#include "render/Frame.h"
#include "ui/Button.h"
#include "util/util.h"

void TrapSelector::draw() {
    for (auto& [e, btn] : m_available) {
        btn->draw();
    }
}
void TrapSelector::update(float dt) {
    for (auto& [e, btn] : m_available) {
        btn->update(dt);
    }
}

void TrapSelector::setActive(const TileEntity* active) {
    if (active == m_pActive) return;

    // Add new decorated frame
    if (!m_pActive) {
        gfx::Drawable* g = m_available[active].release();
        const static float p = 4;
        const static Texture2D tex =
            Resources::getTexture("res/frame_small.png");

        float s = TileGraphic::TILE_WIDTH;
        m_available[active] = std::make_unique<gfx::Frame>(
            tex, std::unique_ptr<gfx::Drawable>(g), p, s, gfx::Frame::Fg);
    }

    // Remove frame
    else if (!active) {
        gfx::Frame* f =
            static_cast<gfx::Frame*>(m_available[m_pActive].release());
        m_available[m_pActive] =
            std::unique_ptr<ui::Button>(f->unwrap<ui::Button>());
        delete f;
    }
    // Move frames
    else {
        setActive(nullptr);
        setActive(active);
    }

    m_pActive = active;
}
void TrapSelector::addEntity(const TileEntity* entity) {
    assert(entity);

    float y = m_position.y;
    for (const auto& [e, btn] : m_available) {
        y += btn->getBoundingBox().height + 5;
    }
    auto btn = std::make_unique<ui::Button>(
        std::unique_ptr<gfx::Drawable>(entity->createGraphic()),
        [=]() { setActive(this->m_pActive == entity ? nullptr : entity); });

    btn->getInternal<gfx::Graphic>()->setPosition({m_position.x, y});
    m_available.emplace(entity, std::move(btn));
    layout();
}
void TrapSelector::layout() {
    size_t i = 0;
    for (auto& [p, btn] : m_available) {
        int x = i % 2;
        int y = i / 2;
        gfx::Graphic* g;
        if (m_pActive == p) {

            g = static_cast<gfx::Frame*>(btn.get())
                    ->getInternal<ui::Button>()
                    ->getInternal<gfx::Graphic>();
        } else {
            g = static_cast<ui::Button*>(btn.get())
                    ->getInternal<gfx::Graphic>();
        }
        Vector2 v = OFFSET;
        v.x += x * WIDTH.x;
        v.y += y * WIDTH.y;
        g->setPosition(v);

        i++;
    }
}