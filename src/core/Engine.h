#pragma once

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

class Engine {
public:
    Engine(ResearchLab* pLab,
        Bank* pBank,
        Lair* pLair,
        UserInterface* pMenu,
        Storyteller* pStoryteller)
        : m_pStoryteller(pStoryteller), m_pMenu(pMenu), m_pLab(pLab),
          m_pBank(pBank), m_pLair(pLair) {}

    /**
     * Event triggered when a request is made to queue a task for research
     * @return Whether the task was successfully queued
     */
    bool researchRequested(ResearchTask* pTask);

    // Event triggered when a research task has completed
    void researchCompleted(ResearchTask* pTask);

    // Event triggered when a research task has been cancelled
    void researchCancelled(ResearchTask* pTask);

    // Event triggered when a tile is added to the lair
    void tileAdded(Tile* tile);

    // Event triggered when a tile is removed from the lair
    void tileRemoved(Tile* tile);

    // Event triggered when a tile is fortified
    void tileFortified(Tile* tile);

    // Event triggered when the balance in the bank is changed
    void balanceChanged(int balance);

    void heroSpawned(Hero* hero);
    void heroDied(Hero* hero);

    void heroInteracted(TileEntity* entity, Hero* hero);

    inline bool shouldQuit() const { return m_shouldQuit; }
    inline void quit() { m_shouldQuit = true; }

private:
    bool m_shouldQuit = false;
    Storyteller* m_pStoryteller;
    UserInterface* m_pMenu;
    ResearchLab* m_pLab;
    Bank* m_pBank;
    Lair* m_pLair;
};