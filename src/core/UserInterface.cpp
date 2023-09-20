#include "UserInterface.h"

#include "SDL_render.h"
#include "SDL_ttf.h"
#include "graphics/HeroGraphic.h"
#include "graphics/TileGraphic.h"

#include "lair/Tile.h"
#include "research/ResearchTask.h"
#include "ui/Button.h"
#include "ui/Label.h"

#include <algorithm>
#include <functional>
#include <iostream>
#include <sstream>
#include <utility>

void UserInterface::addTile(Tile* tile) {
    m_graphics[tile] = new TileGraphic(m_target,
        tile,
        tile->getX() * TileGraphic::TILE_WIDTH + 20,
        tile->getY() * TileGraphic::TILE_WIDTH + 20);
}
bool UserInterface::removeTile(Tile* tile) {
    auto it = m_graphics.find(tile);
    if (it == m_graphics.end()) return false;
    Graphic* g = it->second;
    m_graphics.erase(it->first);
    delete g;
    return true;
}
void UserInterface::setBalance(int balance) {
    std::stringstream s;
    s << "$ " << balance;
    m_balance.setText(s.str());
}

void UserInterface::draw() const {
    SDL_SetRenderDrawColor(m_target, 0xff, 0xff, 0xff, 255);
    SDL_RenderClear(m_target);

    for (const auto& p : m_graphics) {
        p.second->draw();
    }
    for (const auto& p : m_entities) {
        p.second->draw();
    }
    for (const auto& p : m_research) {
        p.second.draw();
    }

    m_balance.draw();
}
void UserInterface::update(uint32_t dt) {
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
    int y = 0;
    for (const auto& [task, graphic] : m_research) {
        y += graphic.getBoundingBox().h + 5;
    }
    ui::Label label(m_target, m_pFont, task->getName());
    label.setPosition({200, y});
    m_research.emplace_back(task, std::move(label));
}
void UserInterface::addHero(Hero* task) {
    assert(m_entities.find(task) == m_entities.end());
    m_entities[task] = new HeroGraphic(m_target, task);
}
bool UserInterface::removeHero(Hero* task) {
    if (m_entities.find(task) == m_entities.end()) return false;
    m_entities.erase(task);
    return true;
}
bool UserInterface::removeResearch(ResearchTask* task) {
    size_t it = std::find_if(m_research.begin(),
                    m_research.end(),
                    [&](const auto& p) { return p.first == task; }) -
                m_research.begin();
    if (it == m_research.size()) return false;

    for (size_t i = it; i < m_research.size() - 1; i++) {
        m_research[i] = std::move(m_research[i + 1]);
    }
    m_research.pop_back();

    int y = 0;
    for (auto& [task, label] : m_research) {
        label.setPosition({200, y});
        y += label.getBoundingBox().h + 5;
    }
    return true;
}