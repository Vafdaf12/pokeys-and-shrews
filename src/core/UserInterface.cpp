#include "UserInterface.h"

#include "SDL_render.h"
#include "SDL_ttf.h"
#include "graphics/HeroGraphic.h"
#include "graphics/TextGraphic.h"
#include "graphics/TileGraphic.h"

#include "lair/Tile.h"
#include "research/ResearchTask.h"

#include <algorithm>
#include <sstream>

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
        p.second->draw();
    }

    m_balance.draw();
}
void UserInterface::addResearch(ResearchTask* task) {
    int y = 0;
    for (auto [task, graphic] : m_research) {
        int h;
        TTF_SizeText(m_pFont, task->getName().c_str(), NULL, &h);
        y += h + 5;
    }
    TextGraphic* g = new TextGraphic(m_target, task->getName(), m_pFont);
    g->setPosition(200, y);
    m_research.emplace_back(task, g);
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

    delete m_research[it].second;

    for (size_t i = it; i < m_research.size() - 1; i++) {
        m_research[i] = m_research[i + 1];
    }
    m_research.pop_back();

    int y = 0;
    for (auto [task, graphic] : m_research) {
        TextGraphic* g = static_cast<TextGraphic*>(graphic);
        g->setPosition(200, y);

        int h;
        TTF_SizeText(m_pFont, task->getName().c_str(), NULL, &h);
        y += h + 5;
    }
    return true;
}