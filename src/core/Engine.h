#pragma once

#include "editor/LairEditor.h"
#include "editor/ResearchManager.h"
#include "editor/TrapSelector.h"
#include "render/Drawable.h"
#include <map>

class UserInterface;
class Storyteller;
class ResearchTask;
class ResearchLab;
class Bank;
class Lair;
class Tile;
class Hero;
class TileEntity;
class GameObject;

class Engine {
public:
    Engine(ResearchLab* pLab,
        Bank* pBank,
        Lair* pLair,
        UserInterface* pMenu,
        Storyteller* pStoryteller,
        TrapSelector* ee)
        : m_pStoryteller(pStoryteller), m_pMenu(pMenu), m_pLab(pLab),
          m_pBank(pBank), m_pLair(pLair), m_entityEditor(ee),
          m_tileEditor(pLair, this), m_researchManager(this) {}

    /**
     * Event triggered when a request is made to queue a task for research
     * @return Whether the task was successfully queued
     */
    bool researchRequested(GameObject* sender, ResearchTask* pTask);

    // Event triggered when a research task has completed
    void researchCompleted(GameObject* sender, ResearchTask* pTask);

    // Event triggered when a research task has been cancelled
    void researchCancelled(GameObject* sender, ResearchTask* pTask);

    // Event triggered when a tile is added to the lair
    void tileAdded(GameObject* sender, Tile* tile);

    // Event triggered when a tile is removed from the lair
    void tileRemoved(GameObject* sender, Tile* tile);

    // Event triggered when a tile is fortified
    void tileFortified(GameObject* sender, Tile* tile);

    // Event triggered when a request is made to place an entity on a tile
    void tileEntityAdded(GameObject* sender, Tile* tile, TileEntity* entity);

    // Event triggered when a request is made to place an entity on a tile
    void tileEntityRemoved(GameObject* sender, Tile* tile, TileEntity* entity);

    // Event triggered when the balance in the bank is changed
    void balanceChanged(GameObject* sender, int balance);

    void heroSpawned(GameObject* sender, Hero* hero);
    void heroDied(GameObject* sender, Hero* hero);

    void heroInteracted(TileEntity* entity, Hero* hero);

    void trapUnlocked(GameObject* sender, TileEntity* entity);

    void waveProgressed(uint32_t required, uint32_t current);
    void waveCompleted(GameObject* sender);

    void gameWon(GameObject* sender);
    void gameOver(GameObject* sender);

    inline bool shouldQuit() const { return m_shouldQuit; }
    inline void quit() { m_shouldQuit = true; }

    inline LairEditor& tileEditor() { return m_tileEditor; }
    inline ResearchManager* researchManager() { return &m_researchManager; }

private:
    static constexpr int TILE_COST = 10;
    static constexpr int FORT_COST = 10;

    bool m_shouldQuit = false;
    Storyteller* m_pStoryteller = nullptr;
    UserInterface* m_pMenu = nullptr;
    ResearchLab* m_pLab = nullptr;
    Bank* m_pBank = nullptr;
    Lair* m_pLair = nullptr;
    TrapSelector* m_entityEditor = nullptr;

    LairEditor m_tileEditor;
    ResearchManager m_researchManager;
};