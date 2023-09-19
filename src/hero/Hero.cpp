#include "Hero.h"

#include "trap/Trap.h"

#include <cassert>

Hero::Hero(
    LairExplorer* explorer, uint32_t health, float speed, Engine* pEngine)
    : m_pExplorer(explorer), m_pEngine(pEngine), m_totalHealth(health),
      m_remainingHealth(health) {
    m_movement = Timer(static_cast<uint32_t>(1000 / speed));
}

void Hero::update(uint32_t dt) {
    m_stunTimer.update(dt);
    m_movement.update(dt);

    if (!m_stunTimer.isComplete()) return;
    if (m_movement.isComplete()) {
        while (m_movement.isComplete())
            m_movement.tick();
        m_pExplorer->next();
    }

    Tile* tile = m_pExplorer->get();
    assert(tile);
    Trap* trap = tile->getTrap();
    if (trap) trap->interact(*this);
}

void Hero::stun(uint32_t time) {
    m_stunTimer.setTime(time);
    m_stunTimer.reset();
}
void Hero::takeDamage(uint32_t damage) {
    if (m_remainingHealth <= damage) {
        m_remainingHealth = 0;
        if (m_pEngine) m_pEngine->heroDied(this);
    } else m_remainingHealth -= damage;
}
