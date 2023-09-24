#include "Engine.h"

#include "core/Storyteller.h"
#include "core/UserInterface.h"
#include "entity/Bank.h"
#include "graphics/TileGraphic.h"
#include "hero/Hero.h"
#include "lair/Lair.h"
#include "lair/Tile.h"
#include "raylib.h"
#include "research/ResearchLab.h"
#include "research/ResearchTask.h"

#include <iostream>

bool Engine::researchRequested(GameObject* sender, ResearchTask* pTask) {
    assert(pTask);

    // Research has been successfully queued
    if (sender == m_pLab) {
        m_pBank->withdraw(pTask->getCost());
        std::cout << "[ENGINE] research queued: " << pTask->toString()
                  << std::endl;
        return true;
    }

    // Request is made from in-game object
    if (!m_pBank->sufficientFunds(pTask->getCost())) {
        std::cout << "[ENGINE] insuffient funds: " << pTask->toString()
                  << std::endl;
        return false;
    }

    m_pLab->enqueue(pTask);
    return true;
}

void Engine::researchCompleted(GameObject* sender, ResearchTask* pTask) {
    assert(pTask);
    m_researchManager.removeResearch(pTask);
    std::cout << "[ENGINE] research completed: " << pTask->toString()
              << std::endl;
}

void Engine::researchCancelled(GameObject* sender, ResearchTask* pTask) {
    assert(pTask);

    // Task has been successfully removed
    if (sender == m_pLab) {
        // m_researchManager.removeResearch(pTask);
        return;
    }

    // Request sent from user interface
    if (!m_pLab->cancel(pTask)) {
        std::cout << "[ENGINE] cancel research failed: " << pTask->toString()
                  << std::endl;
        return;
    }

    m_pBank->deposit(pTask->getCost());
    std::cout << "[ENGINE] research cancelled: " << pTask->toString()
              << std::endl;
}

void Engine::tileAdded(GameObject* sender, Tile* tile) {
    if (sender == &m_tileEditor) {
        if (m_pBank->sufficientFunds(TILE_COST)) {
            m_pLair->addTile(tile->getX(), tile->getY());
        }
        return;
    }
    m_pBank->withdraw(TILE_COST);
    m_tileEditor.addTile(*tile);
    m_pStoryteller->addSpawnTile(tile);
    std::cout << "[ENGINE] tile added at: (" << tile->getX() << ", "
              << tile->getY() << ")" << std::endl;
}
void Engine::tileRemoved(GameObject* sender, Tile* tile) {
    if (sender == &m_tileEditor) {
        if (!m_pStoryteller->isHeroOnTile(tile))
            m_pLair->removeTile(tile->getX(), tile->getY());
        return;
    }
    m_pBank->deposit(TILE_COST);
    m_tileEditor.removeTile(*tile);
    m_pStoryteller->removeSpawnTile(tile);
    std::cout << "[ENGINE] tile removed at: (" << tile->getX() << ", "
              << tile->getY() << ")" << std::endl;
}
void Engine::tileFortified(GameObject* sender, Tile* tile) {
    if (sender == &m_tileEditor) {
        if (m_pBank->sufficientFunds(FORT_COST)) {
            m_pLair->fortifyTile(tile->getX(), tile->getY());
        }
        return;
    }
    m_pBank->withdraw(FORT_COST);
    m_pStoryteller->removeSpawnTile(tile);
    std::cout << "[ENGINE] tile fortified at: (" << tile->getX() << ", "
              << tile->getY() << ")" << std::endl;
}
void Engine::balanceChanged(GameObject* sender, int balance) {
    std::cout << "[ENGINE] balance changed: $" << balance << std::endl;
    m_pMenu->setBalance(balance);
    if (balance <= 0) gameOver(sender);
}

void Engine::heroSpawned(GameObject* sender, Hero* hero) {
    std::cout << "[ENGINE] hero spawned" << std::endl;
    m_pMenu->addHero(hero);
}
void Engine::heroDied(GameObject* sender, Hero* hero) {
    // Hero successfully died
    if (sender == m_pStoryteller) {
        m_pMenu->removeHero(hero);
        m_pBank->deposit(hero->getTotalHealth());
        std::cout << "[ENGINE] hero died" << std::endl;
        return;
    }

    // Send request
    m_pStoryteller->killHero(hero);
}
void Engine::heroInteracted(TileEntity* entity, Hero* hero) {
    if (entity == m_pBank) gameOver(entity);
}
void Engine::tileEntityAdded(
    GameObject* sender, Tile* tile, TileEntity* entity) {
    if (sender == &m_tileEditor) {
        if (!m_entityEditor->getActive()) return;
        TileEntity* entity = m_entityEditor->getActive()->clone();
        m_pLair->addEntity(tile->getX(), tile->getY(), entity);
        return;
    }
    m_tileEditor.addTileEntity(*tile, *entity);
}
void Engine::tileEntityRemoved(
    GameObject* sender, Tile* tile, TileEntity* entity) {
    if (sender == &m_tileEditor) {
        m_pLair->removeEntity(tile->getX(), tile->getY());
        return;
    }
    m_tileEditor.removeTileEntity(*entity);
}
void Engine::trapUnlocked(GameObject* sender, TileEntity* entity) {
    m_entityEditor->addEntity(entity);
}
void Engine::waveProgressed(uint32_t required, uint32_t current) {
    m_pMenu->setProgress(current, required);
}

void Engine::waveCompleted(GameObject* sender) {
    std::cout << "[ENGINE] Wave completed!!" << std::endl;
    m_pLair->reset();
    m_pStoryteller->reset();

    m_pStoryteller->nextWave();
}
void Engine::gameWon(GameObject* sender) {
    std::cout << "[ENGINE] You defeated all the heroes!!" << std::endl;
    m_shouldQuit = true;
}
void Engine::gameOver(GameObject* sender) {
    std::cout << "[ENGINE] bank discovered!!!" << std::endl;
    m_shouldQuit = true;
}