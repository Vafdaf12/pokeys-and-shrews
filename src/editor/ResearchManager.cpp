#include "ResearchManager.h"

#include "core/Engine.h"
#include "core/Resources.h"
#include "editor/ResearchManager.h"
#include "graphics/TileGraphic.h"
#include "raylib.h"
#include "render/Drawable.h"
#include "render/Frame.h"
#include "ui/Button.h"

#include <algorithm>
#include <stdio.h>
#include <string>

void ResearchManager::addResearch(ResearchTask* task) {
    auto btn = std::make_unique<ui::Button>(
        std::unique_ptr<gfx::Graphic>(task->createGraphic()),
        std::bind(&ResearchManager::onClick, this, task));
    m_research.emplace(task, std::move(btn));
    layout();
}
bool ResearchManager::removeResearch(const ResearchTask* task) {
    auto it = m_research.find(task);
    if (it == m_research.end()) return false;
    m_research.erase(it);
    layout();

    return true;
}
void ResearchManager::onClick(ResearchTask* task) {
    if (!m_pEngine) return;
    if (m_enqueued.contains(task)) {
        m_pEngine->researchCancelled(this, task);
        m_enqueued.erase(task);

        gfx::Frame* f = static_cast<gfx::Frame*>(m_research[task].release());
        m_research[task] = std::unique_ptr<ui::Button>(f->unwrap<ui::Button>());
        delete f;
    } else if (m_pEngine->researchRequested(this, task)) {
        m_enqueued.insert(task);

        gfx::DrawableDecorator* g = m_research[task].release();
        const static Texture2D tex =
            Resources::getTexture("res/research_counter.png");

        float s = TileGraphic::TILE_WIDTH;
        m_research[task] = std::make_unique<gfx::Frame>(
            tex, std::unique_ptr<gfx::Drawable>(g), 0, s, gfx::Frame::Fg);
    }
}
void ResearchManager::layout() {
    size_t i = 0;
    for (auto& [ptr, btn] : m_research) {
        int x = i % 2;
        int y = i / 2;
        i++;
        gfx::Graphic* g;
        if (m_enqueued.contains(ptr)) {
            g = btn->getInternal<ui::Button>()->getInternal<gfx::Graphic>();

        } else {
            g = btn->getInternal<gfx::Graphic>();
        }

        Vector2 v = OFFSET;
        v.x += x * WIDTH.x;
        v.y += y * WIDTH.y;
        g->setPosition(v);
    }
}
gfx::Rect ResearchManager::getBoundingBox() const {
    if (m_research.empty()) return {OFFSET.x, OFFSET.y, 0, 0};
    gfx::Rect r = m_research.begin()->second->getBoundingBox();
    Vector2 topLeft = {r.x, r.y};
    Vector2 bottomRight = {r.x + r.width, r.y + r.height};

    for (auto it = ++m_research.begin(); it != m_research.end(); it++) {
        r = it->second->getBoundingBox();
        topLeft.x = std::min(topLeft.x, r.x);
        topLeft.y = std::min(topLeft.y, r.y);

        bottomRight.x = std::max(topLeft.x, r.x + r.width);
        bottomRight.y = std::max(topLeft.y, r.y + r.height);
    }
    return {
        topLeft.x,
        topLeft.y,
        bottomRight.x - topLeft.x,
        bottomRight.y - topLeft.y,
    };
}
void ResearchManager::draw() {
    for (auto& p : m_research) {
        p.second->draw();
    }
}
void ResearchManager::update(float dt) {
    for (auto& [ptr, btn] : m_research) {
        btn->update(dt);
    }
}