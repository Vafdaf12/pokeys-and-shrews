#include "Hero.h"

#include "trap/Trap.h"

#include <cassert>

Hero::Hero(LairExplorer* explorer, uint32_t health, float speed)
    : m_pExplorer(explorer), m_totalHealth(health), m_remainingHealth(health) {
    m_movement = Timer(1000 / speed);
    m_interactTimer = Timer(250);
}

void Hero::update(uint32_t dt) {
    m_stunTimer.update(dt);
    if (!m_stunTimer.isComplete()) return;

    m_movement.update(dt);
    if (m_movement.isComplete()) {
        m_movement.tick();
        m_pExplorer->next();
        m_interactTimer.reset();
    }

    m_interactTimer.update(dt);
    if (m_interactTimer.isComplete()) {
        m_interactTimer.tick();
        Tile* tile = m_pExplorer->get();
        assert(tile);
        Trap* trap = tile->getTrap();
        if (trap) trap->interact(*this);
    }
}

void Hero::stun(uint32_t time) {
    m_stunTimer.setTime(time);
    m_stunTimer.reset();
}
void Hero::takeDamage(uint32_t damage) {
    if (m_remainingHealth < damage) {
        m_remainingHealth = 0;
    } else m_remainingHealth -= damage;
}
