#pragma once

#include "SDL_ttf.h"
#include "core/Graphic.h"
#include "core/UserInterface.h"
#include "graphics/TextGraphic.h"
#include "research/ResearchTask.h"
#include <map>
#include <vector>

class Tile;

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
    void removeResearch(ResearchTask* task);

    void draw() const override;

private:
    TTF_Font* m_pFont;
    TextGraphic m_balance;
    std::map<void*, Graphic*> m_graphics;
    std::vector<std::pair<ResearchTask*, Graphic*>> m_research;
};