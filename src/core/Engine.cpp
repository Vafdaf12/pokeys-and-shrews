#include "Engine.h"

#include "core/Storyteller.h"
#include "core/UserInterface.h"
#include "entity/Bank.h"
#include "graphics/TileGraphic.h"
#include "hero/Hero.h"
#include "lair/Lair.h"
#include "lair/Tile.h"
#include "research/ResearchLab.h"
#include "research/ResearchTask.h"

#include <iostream>

bool Engine::researchRequested(GameObject* sender, ResearchTask* pTask) {
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

void Engine::researchCompleted(GameObject* sender, ResearchTask* pTask) {
    assert(pTask);
    m_pMenu->removeResearch(pTask);
    std::cout << "[ENGINE] research completed: " << *pTask << std::endl;
}

void Engine::researchCancelled(GameObject* sender, ResearchTask* pTask) {
    assert(pTask);

    // Request sent from research lab
    if (sender == pTask) {
        m_pMenu->removeResearch(pTask);
    }

    // Request sent from user interface
    if (sender == m_pMenu) {
        if (m_pLab->cancel(pTask)) {
            m_pBank->deposit(pTask->getCost());
            std::cout << "[ENGINE] research cancelled: " << *pTask << std::endl;
        }
    }
}

void Engine::tileAdded(GameObject* sender, Tile* tile) {
    m_pMenu->addTile(tile);
    m_pStoryteller->addSpawnTile(tile);
    std::cout << "[ENGINE] tile added at: (" << tile->getX() << ", "
              << tile->getY() << ")" << std::endl;
}
void Engine::tileRemoved(GameObject* sender, Tile* tile) {
    m_pMenu->removeTile(tile);
    m_pStoryteller->removeSpawnTile(tile);
    std::cout << "[ENGINE] tile removed at: (" << tile->getX() << ", "
              << tile->getY() << ")" << std::endl;
}
void Engine::tileFortified(GameObject* sender, Tile* tile) {
    m_pStoryteller->removeSpawnTile(tile);
    std::cout << "[ENGINE] tile fortified at: (" << tile->getX() << ", "
              << tile->getY() << ")" << std::endl;
}
void Engine::balanceChanged(GameObject* sender, int balance) {
    std::cout << "[ENGINE] balance changed: $" << balance << std::endl;
    m_pMenu->setBalance(balance);
}

void Engine::heroSpawned(GameObject* sender, Hero* hero) {
    std::cout << "[ENGINE] hero spawned" << std::endl;
    m_pMenu->addHero(hero);
}
void Engine::heroDied(GameObject* sender, Hero* hero) {
    std::cout << "[ENGINE] hero died" << std::endl;
    // Update GUI
    m_pMenu->removeHero(hero);

    // Storyteller is removing heroes
    if (sender == m_pStoryteller) return;

    m_pBank->deposit(hero->getTotalHealth());
    m_pStoryteller->killHero(hero);
}
void Engine::heroInteracted(TileEntity* entity, Hero* hero) {
    if (entity == m_pBank) {
        std::cout << "[ENGINE] bank discovered!!!" << std::endl;
        quit();
    }
}
void Engine::tileEntityAdded(
    GameObject* sender, Tile* tile, TileEntity* entity) {
    m_pMenu->addTileEntity(tile, entity);
}
void Engine::tileEntityRemoved(
    GameObject* sender, Tile* tile, TileEntity* entity) {
    m_pMenu->removeTileEntity(entity);
}
void Engine::trapUnlocked(GameObject* sender, TileEntity* entity) {
    m_entityEditor->addEntity(entity);
}
void Engine::waveProgressed(uint32_t required, uint32_t current) {
    m_pMenu->setProgress(current, required);
    if (current >= required) {
        m_pLair->reset();
        m_pStoryteller->reset();
    }
}
