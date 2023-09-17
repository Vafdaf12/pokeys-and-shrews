#include "Engine.h"

#include "SDL_rect.h"
#include "SDL_render.h"

#include "bank/Bank.h"
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
    std::cout << "[ENGINE] research queued: " << *pTask << std::endl;
    return true;
}

void Engine::researchCompleted(ResearchTask* pTask) {
    assert(pTask);
    std::cout << "[ENGINE] research completed: " << *pTask << std::endl;
}

void Engine::researchCancelled(ResearchTask* pTask) {
    assert(pTask);
    std::cout << "[ENGINE] research cancelled: " << *pTask << std::endl;
    m_pBank->deposit(pTask->getCost());
}

void Engine::tileAdded(Tile* tile) { m_pMenu->addTile(tile); }
void Engine::tileRemoved(Tile* tile) { m_pMenu->removeTile(tile); }
void Engine::balanceChanged(int balance) { m_pMenu->setBalance(balance); }