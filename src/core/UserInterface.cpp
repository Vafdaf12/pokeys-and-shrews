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

UserInterface::UserInterface(Font font, Engine* pEngine)
    : GameObject(pEngine), m_font(font),
      m_uiFrame(Resources::getTexture("res/ui_empty.png")),
      m_balance(font, "??"), m_progress(font, "0/0") {
    static Color textColor = {255, 211, 0, 255};
    m_progress.setForeground(textColor);
    m_balance.setPosition({70, 17});
    m_balance.setForeground(textColor);
    m_progress.setPosition({680, 17});
    ;
}
void UserInterface::setBalance(int balance) {
    m_balance.setText(std::to_string(balance));
}
void UserInterface::setProgress(uint32_t current, uint32_t total) {
    std::stringstream s;
    s << current << "/" << total;
    m_progress.setText(s.str());
}

void UserInterface::reload() {

    m_uiFrame = Resources::getTexture("res/ui_empty.png", true);
}
void UserInterface::draw() {
    float scale = float(GetScreenWidth()) / m_uiFrame.width;
    DrawTextureEx(m_uiFrame, {0, 0}, 0, scale, WHITE);

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
        y += btn.getInternal()->getBoundingBox().height + 5;
    }
    ui::Button btn(std::unique_ptr<gfx::Graphic>(task->createGraphic()), [=]() {
        if (m_pEngine) m_pEngine->researchCancelled(this, task);
    });

    btn.getInternal<gfx::Graphic>()->setPosition({0, y});
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
        gfx::Graphic* label = btn.getInternal<gfx::Graphic>();
        label->setPosition({0, y});
        y += label->getBoundingBox().height + 5;
    }
    return true;
}