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