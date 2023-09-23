#include "UserInterface.h"

#include "graphics/HeroGraphic.h"
#include "graphics/TileGraphic.h"

#include "entity/TileEntity.h"
#include "hero/Hero.h"
#include "lair/Tile.h"
#include "raylib.h"
#include "research/ResearchTask.h"
#include "ui/Button.h"
#include "ui/Label.h"

#include <algorithm>
#include <functional>
#include <iostream>
#include <sstream>
#include <utility>

void UserInterface::setBalance(int balance) {
    std::stringstream s;
    s << "$ " << balance;
    m_balance.setText(s.str());
}
void UserInterface::setProgress(uint32_t current, uint32_t total) {
    std::stringstream s;
    s << current << "/" << total;
    m_progress.setText(s.str());
}

void UserInterface::draw() {
    ClearBackground({255, 255, 255, 255});

    m_balance.setPosition({0, 0});
    std::vector<ui::Label*> labels = {&m_balance, &m_progress};
    for (int i = 1; i < labels.size(); i++) {
        Rectangle rect = labels[i - 1]->getBoundingBox();
        labels[i]->setPosition({rect.x + rect.width + 20, rect.y});
    }

    for (const auto& p : m_graphics) {
        p.second->draw();
    }
    for (const auto& p : m_tileEntities) {
        p.second->draw();
    }
    for (const auto& p : m_entities) {
        p.second->draw();
    }
    for (auto& p : m_research) {
        p.second.draw();
    }

    m_balance.draw();
    m_progress.draw();
}
void UserInterface::update(float dt) {
    for (const auto& p : m_graphics) {
        p.second->update(dt);
    }
    for (const auto& p : m_entities) {
        p.second->update(dt);
    }
    for (auto& p : m_research) {
        p.second.update(dt);
    }
}
void UserInterface::addResearch(ResearchTask* task) {
    float y = m_balance.getBoundingBox().height + 20;
    for (const auto& [task, btn] : m_research) {
        y += btn.getGraphic()->getBoundingBox().height + 5;
    }
    ui::Button btn(task->createGraphic(), [=]() {
        if (m_pEngine) m_pEngine->researchCancelled(this, task);
    });

    btn.getGraphic()->setPosition({0, y});
    m_research.emplace_back(task, std::move(btn));
}
void UserInterface::addHero(Hero* task) {
    assert(m_entities.find(task) == m_entities.end());
    m_entities[task] = std::unique_ptr<Graphic>(task->createGraphic());
}
bool UserInterface::removeHero(Hero* task) {
    if (m_entities.find(task) == m_entities.end()) return false;
    m_entities.erase(task);
    return true;
}
bool UserInterface::removeResearch(ResearchTask* task) {
    auto it = std::remove_if(m_research.begin(),
        m_research.end(),
        [&](const auto& p) { return p.first == task; });
    if (it == m_research.end()) return false;
    m_research.erase(it);

    float y = m_balance.getBoundingBox().height + 20;
    for (auto& [task, btn] : m_research) {
        gfx::Graphic* label = btn.getGraphic();
        label->setPosition({0, y});
        y += label->getBoundingBox().height + 5;
    }
    return true;
}