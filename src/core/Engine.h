#pragma once

#include "editor/EntityEditor.h"
#include <map>

class UserInterface;
class Storyteller;
class ResearchTask;
class ResearchLab;
class Bank;
class Graphic;
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
        EntityEditor* ee)
        : m_pStoryteller(pStoryteller), m_pMenu(pMenu), m_pLab(pLab),
          m_pBank(pBank), m_pLair(pLair), m_entityEditor(ee) {}

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

    inline bool shouldQuit() const { return m_shouldQuit; }
    inline void quit() { m_shouldQuit = true; }

private:
    bool m_shouldQuit = false;
    Storyteller* m_pStoryteller;
    UserInterface* m_pMenu;
    ResearchLab* m_pLab;
    Bank* m_pBank;
    Lair* m_pLair;
    EntityEditor* m_entityEditor;
};