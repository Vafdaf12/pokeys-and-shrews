#pragma once

#include "core/Engine.h"
#include "core/GameObject.h"
#include "core/Timer.h"
#include "lair/Lair.h"
#include "lair/LairExplorer.h"

class Hero : public GameObject {
public:
    Hero(LairExplorer* explorer,
        uint32_t health,
        float speed,
        uint32_t damage,
        Engine* pEngine = nullptr);

    friend class HeroGraphic;
    Graphic* createGraphic() const override;

    void update(float dt);

    void stun(uint32_t time);
    void takeDamage(uint32_t damage);

    inline bool isDead() const { return m_remainingHealth == 0; }
    inline LairExplorer* getExplorer() { return m_pExplorer; }
    inline const LairExplorer* getExplorer() const { return m_pExplorer; }
    inline uint32_t getTotalHealth() const { return m_totalHealth; }
    inline uint32_t getDamage() const { return m_damage; }

private:
    Timer m_stunTimer;
    Timer m_movement;
    LairExplorer* m_pExplorer;

    uint32_t m_totalHealth;
    uint32_t m_damage;
    uint32_t m_remainingHealth;
};