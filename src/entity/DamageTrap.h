#pragma once

#include "TileEntity.h"

#include "core/Engine.h"
#include "hero/Hero.h"

class DamageTrap : public TileEntity {
public:
    DamageTrap(int damage, Engine* pEngine = nullptr)
        : TileEntity(pEngine), m_damage(damage) {}

    void interact(Hero& hero) override {
        hero.takeDamage(m_damage);
        hero.stun(2000);
    }

private:
    uint32_t m_damage;
};