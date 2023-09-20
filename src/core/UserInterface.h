#pragma once

#include "SDL_ttf.h"
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
class EventLoop;

class UserInterface : public Graphic {
public:
    UserInterface(TargetType target,
        TTF_Font* pFont,
        EventLoop* eventLoop,
        Engine* pEngine = nullptr)
        : Graphic(target), m_pEngine(pEngine), m_pFont(pFont),
          m_eventLoop(eventLoop), m_balance(target, pFont, "$ N/A") {}

    inline void setEngine(Engine* pEngine) { m_pEngine = pEngine; }

    /// Adds a graphics a render a tile
    void addTile(Tile* tile);

    /// Removes the graphic corresponding the passed-in tile
    bool removeTile(Tile* tile);

    /// Sets the displayed bank balance
    void setBalance(int balance);

    void addResearch(ResearchTask* task);
    bool removeResearch(ResearchTask* task);

    void addHero(Hero* hero);
    bool removeHero(Hero* hero);

    void draw() const override;
    void update(uint32_t dt) override;

private:
    Engine* m_pEngine;
    TTF_Font* m_pFont;
    EventLoop* m_eventLoop;
    ui::Label m_balance;
    std::map<void*, Graphic*> m_graphics;
    std::map<void*, Graphic*> m_entities;
    std::vector<std::pair<ResearchTask*, Graphic*>> m_research;
};