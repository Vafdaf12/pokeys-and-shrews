#pragma once

#include "core/Graphic.h"
#include <map>
class ResearchTask;
class ResearchLab;
class Bank;
class Graphic;
class Lair;
class Tile;

class Engine {
public:
    Engine(ResearchLab* pLab, Bank* pBank, Lair* pLair)
        : m_pLab(pLab), m_pBank(pBank), m_pLair(pLair) {}

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

    void draw(RenderTarget target) const;

private:
    std::map<void*, Graphic*> m_graphics;

    ResearchLab* m_pLab;
    Bank* m_pBank;
    Lair* m_pLair;
};