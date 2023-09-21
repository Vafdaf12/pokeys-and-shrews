#pragma once

#include "core/Engine.h"
#include "core/Graphic.h"
#include "core/UserInterface.h"
#include "ui/Button.h"
#include "ui/Label.h"
#include <map>
#include <vector>

class Tile;
class Hero;
class ResearchTask;

class UserInterface : public Graphic {
public:
    UserInterface(Font font, Engine* pEngine = nullptr)
        : m_pEngine(pEngine), m_font(font), m_balance(font, "$ N/A") {}

    /// Adds a graphics a render a tile
    void addTile(Tile* tile);

    /// Adds a graphics a render a tile entity
    void addTileEntity(Tile* tile, TileEntity* entity);

    /// Removes the graphic corresponding the passed-in tile
    bool removeTile(Tile* tile);

    /// Removes the graphic corresponding the passed-in tile entity
    bool removeTileEntity(TileEntity* entity);

    /// Sets the displayed bank balance
    void setBalance(int balance);

    void addResearch(ResearchTask* task);
    bool removeResearch(ResearchTask* task);

    void addHero(Hero* hero);
    bool removeHero(Hero* hero);

    void draw() override;
    void update(float dt) override;

    inline void setEngine(Engine* pEngine) { m_pEngine = pEngine; }

private:
    Engine* m_pEngine;
    Font m_font;
    ui::Label m_balance;
    std::map<void*, Graphic*> m_graphics;
    std::map<void*, Graphic*> m_tileEntities;
    std::map<void*, Graphic*> m_entities;
    std::vector<std::pair<ResearchTask*, ui::Button>> m_research;
};