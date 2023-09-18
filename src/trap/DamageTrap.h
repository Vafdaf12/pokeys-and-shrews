#pragma once

#include "Trap.h"
#include "hero/Hero.h"

class DamageTrap : public Trap {
public:
    DamageTrap(int damage) : m_damage(damage) {}

    void interact(Hero& hero) override {
        hero.takeDamage(m_damage);
        hero.stun(2000);
    }

private:
    uint32_t m_damage;
};