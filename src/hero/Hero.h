#pragma once

#include "core/Engine.h"
#include "core/Timer.h"
#include "lair/Lair.h"
#include "lair/LairExplorer.h"

class Hero {
public:
    Hero(LairExplorer* explorer,
        uint32_t health,
        float speed,
        Engine* pEngine = nullptr);
    friend class HeroGraphic;

    void update(uint32_t dt);

    void stun(uint32_t time);
    void takeDamage(uint32_t damage);

    inline bool isDead() const { return m_remainingHealth == 0; }
    inline LairExplorer* getExplorer() { return m_pExplorer; }

private:
    Timer m_stunTimer;
    Timer m_movement;
    LairExplorer* m_pExplorer;
    Engine* m_pEngine;

    uint32_t m_totalHealth;
    uint32_t m_remainingHealth;
};