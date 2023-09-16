#include "Engine.h"

#include "SDL_rect.h"
#include "SDL_render.h"
#include "bank/Bank.h"
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

void Engine::tileAdded(Tile* tile) {
    m_graphics[tile] = new TileGraphic(tile,
        tile->getX() * TileGraphic::TILE_WIDTH + 20,
        tile->getY() * TileGraphic::TILE_WIDTH + 20);
}

void Engine::tileRemoved(Tile* tile) {
    auto it = m_graphics.find(tile);
    if (it == m_graphics.end()) return;
    m_graphics.erase(it->first);
}

void Engine::draw(RenderTarget target) const {
    SDL_SetRenderDrawColor(target, 0xff, 0xff, 0xff, 255);
    SDL_RenderClear(target);

    SDL_SetRenderDrawColor(target, 0xff, 0x00, 0x00, 255);
    SDL_Rect rect = {20,
        20,
        static_cast<int>(m_pLair->getWidth() * TileGraphic::TILE_WIDTH),
        static_cast<int>(m_pLair->getHeight() * TileGraphic::TILE_WIDTH)};

    SDL_RenderDrawRect(target, &rect);

    for (const auto& p : m_graphics) {
        p.second->draw(target);
    }
}