#pragma once

#include "SDL_ttf.h"
#include "core/Graphic.h"
#include "core/UserInterface.h"
#include "graphics/TextGraphic.h"
#include <map>
#include <vector>

class Tile;
class Hero;
class ResearchTask;

class UserInterface : public Graphic {
public:
    UserInterface(TargetType target, TTF_Font* pFont)
        : Graphic(target), m_pFont(pFont), m_balance(target, "$ N/A", pFont) {}

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
    TTF_Font* m_pFont;
    TextGraphic m_balance;
    std::map<void*, Graphic*> m_graphics;
    std::map<void*, Graphic*> m_entities;
    std::vector<std::pair<ResearchTask*, Graphic*>> m_research;
};