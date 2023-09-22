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

void UserInterface::addTile(Tile* tile) {
    m_graphics[tile] = std::make_unique<TileGraphic>(tile,
        tile->getX() * TileGraphic::TILE_WIDTH + MAP_OFFSET.x,
        tile->getY() * TileGraphic::TILE_WIDTH + MAP_OFFSET.y);
}
bool UserInterface::removeTile(Tile* tile) {
    if (m_graphics.find(tile) == m_graphics.end()) return false;
    m_graphics.erase(tile);
    return true;
}
void UserInterface::setBalance(int balance) {
    std::stringstream s;
    s << "$ " << balance;
    m_balance.setText(s.str());
}

void UserInterface::draw() {
    ClearBackground({255, 255, 255, 255});

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
    for (const auto& [task, graphic] : m_research) {
        y += graphic.getBoundingBox().height + 5;
    }
    ui::Button label(m_font, task->getName(), [=]() {
        if (m_pEngine) m_pEngine->researchCancelled(this, task);
    });
    label.setPosition({0, y});
    m_research.emplace_back(task, std::move(label));
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
    for (auto& [task, label] : m_research) {
        label.setPosition({0, y});
        y += label.getBoundingBox().height + 5;
    }
    return true;
}
void UserInterface::addTileEntity(Tile* tile, TileEntity* entity) {
    assert(tile);
    assert(entity);
    assert(m_graphics.find(tile) != m_graphics.end());
    Vector2 pos = m_graphics[tile]->getPosition();

    std::unique_ptr<Graphic> graphic(entity->createGraphic());
    graphic->setPosition(pos);
    m_tileEntities[entity] = std::move(graphic);
}
bool UserInterface::removeTileEntity(TileEntity* entity) {
    assert(entity);
    if (m_tileEntities.find(entity) == m_tileEntities.end()) return false;
    m_tileEntities.erase(entity);
    return true;
}