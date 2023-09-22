#pragma once

#include "core/Engine.h"
#include "core/GameObject.h"
#include "core/Graphic.h"
#include "core/UserInterface.h"
#include "raylib.h"
#include "ui/Button.h"
#include "ui/Label.h"

#include <map>
#include <memory>
#include <vector>

class Tile;
class Hero;
class ResearchTask;

class UserInterface : public Graphic, public GameObject {
public:
    constexpr static Vector2 MAP_OFFSET = {200, 20};

    UserInterface(Font font, Engine* pEngine = nullptr)
        : GameObject(pEngine), m_font(font), m_balance(font, "$"),
          m_progress(font, "0/0") {}

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

    /// Sets the displayed wave progress
    void setProgress(uint32_t current, uint32_t total);

    void addResearch(ResearchTask* task);
    bool removeResearch(ResearchTask* task);

    void addHero(Hero* hero);
    bool removeHero(Hero* hero);

    void draw() override;
    void update(float dt) override;

    inline void setEngine(Engine* pEngine) { m_pEngine = pEngine; }
    inline Rectangle getBoundingBox() const override {
        assert(false && "Not bounding box for user interface");
        return {0, 0, 0, 0};
    }

private:
    Font m_font;
    ui::Label m_balance;
    ui::Label m_progress;
    std::map<const void*, std::unique_ptr<Graphic>> m_graphics;
    std::map<const void*, std::unique_ptr<Graphic>> m_tileEntities;
    std::map<const void*, std::unique_ptr<Graphic>> m_entities;
    std::vector<std::pair<ResearchTask*, ui::Button>> m_research;
};