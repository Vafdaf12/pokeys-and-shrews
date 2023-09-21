#include "Hero.h"

#include "entity/TileEntity.h"
#include "graphics/HeroGraphic.h"

#include <cassert>

Hero::Hero(LairExplorer* explorer,
    uint32_t health,
    float speed,
    uint32_t damage,
    Engine* pEngine)
    : GameObject(pEngine), m_pExplorer(explorer), m_totalHealth(health),
      m_damage(damage), m_remainingHealth(health) {
    m_movement = Timer(1 / speed);
}

void Hero::update(float dt) {
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
    TileEntity* trap = tile->getEntity();
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
Graphic* Hero::createGraphic() const { return new HeroGraphic(this); }
