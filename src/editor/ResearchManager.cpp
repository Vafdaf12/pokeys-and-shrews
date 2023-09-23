#include "ResearchManager.h"

#include "core/Engine.h"
#include "editor/ResearchManager.h"
#include "raylib.h"
#include "render/Drawable.h"

#include <algorithm>
#include <stdio.h>

void ResearchManager::addResearch(ResearchTask* task) {
    ui::Button btn(std::unique_ptr<gfx::Graphic>(task->createGraphic()), [=]() {
        if (m_pEngine) m_pEngine->researchCancelled(this, task);
    });
    m_research.emplace_back(task, std::move(btn));
    layout();
}
bool ResearchManager::removeResearch(const ResearchTask* task) {
    auto it = std::remove_if(m_research.begin(),
        m_research.end(),
        [&](const auto& p) { return p.first == task; });
    if (it == m_research.end()) return false;
    m_research.erase(it);
    layout();

    return true;
}
void ResearchManager::layout() {
    for (size_t i = 0; i < m_research.size(); i++) {
        int x = i % 2;
        int y = i / 2;
        gfx::Graphic* g = m_research[i].second.getInternal<gfx::Graphic>();
        Vector2 v = OFFSET;
        v.x += x * WIDTH.x;
        v.y += y * WIDTH.y;
        g->setPosition(v);
    }
}
gfx::Rect ResearchManager::getBoundingBox() const {
    if (m_research.empty()) return {OFFSET.x, OFFSET.y, 0, 0};
    gfx::Rect r = m_research[0].second.getBoundingBox();
    Vector2 topLeft = {r.x, r.y};
    Vector2 bottomRight = {r.x + r.width, r.y + r.height};

    for (size_t i = 1; i < m_research.size(); i++) {
        r = m_research[i].second.getBoundingBox();
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
        p.second.draw();
    }
}
void ResearchManager::update(float dt) {
    for (auto& p : m_research) {
        p.second.update(dt);
    }
}
