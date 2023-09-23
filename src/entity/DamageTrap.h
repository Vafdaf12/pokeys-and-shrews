#pragma once

#include "TileEntity.h"

#include "core/Engine.h"
#include "graphics/trap/DamageTrapGraphic.h"
#include "hero/Hero.h"

class DamageTrap : public TileEntity {
public:
    DamageTrap(int damage, Engine* pEngine = nullptr)
        : TileEntity(pEngine), m_damage(damage) {}

    void interact(Hero& hero) override {
        hero.takeDamage(m_damage);
        hero.stun(2);
    }
    inline TileEntity* clone() const override {
        return new DamageTrap(m_damage, m_pEngine);
    }
    inline gfx::Graphic* createGraphic() const override {
        return new DamageTrapGraphic(this);
    }

private:
    uint32_t m_damage;
};