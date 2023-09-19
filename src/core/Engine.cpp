#include "Engine.h"

#include "SDL_rect.h"
#include "SDL_render.h"

#include "bank/Bank.h"
#include "core/Storyteller.h"
#include "core/UserInterface.h"
#include "graphics/TileGraphic.h"
#include "lair/Lair.h"
#include "lair/Tile.h"
#include "research/ResearchLab.h"
#include "research/ResearchTask.h"

#include <iostream>

bool Engine::researchRequested(ResearchTask* pTask) {
    assert(pTask);
    if (!m_pBank->sufficientFunds(pTask->getCost())) {
        std::cout << "[ENGINE] insuffient funds: " << *pTask << std::endl;
        return false;
    }
    m_pBank->withdraw(pTask->getCost());
    m_pLab->enqueue(pTask);
    m_pMenu->addResearch(pTask);
    return true;
}

void Engine::researchCompleted(ResearchTask* pTask) {
    assert(pTask);
    m_pMenu->removeResearch(pTask);
    std::cout << "[ENGINE] research completed: " << *pTask << std::endl;
}

void Engine::researchCancelled(ResearchTask* pTask) {
    assert(pTask);
    m_pMenu->removeResearch(pTask);
    std::cout << "[ENGINE] research cancelled: " << *pTask << std::endl;
    m_pBank->deposit(pTask->getCost());
}

void Engine::tileAdded(Tile* tile) {
    m_pMenu->addTile(tile);
    m_pStoryteller->addSpawnTile(tile);
}
void Engine::tileRemoved(Tile* tile) {
    m_pMenu->removeTile(tile);
    m_pStoryteller->removeSpawnTile(tile);
}
void Engine::tileFortified(Tile* tile) {
    m_pStoryteller->removeSpawnTile(tile);
}
void Engine::balanceChanged(int balance) { m_pMenu->setBalance(balance); }