#pragma once

#include "TileEntity.h"

#include "graphics/trap/StunTrapGraphic.h"
#include "hero/Hero.h"

class StunTrap : public TileEntity {
public:
    StunTrap(float duration, float cooldown, Engine* pEngine = nullptr)
        : TileEntity(pEngine), m_cooldown(cooldown, true),
          m_duration(duration) {}

    inline TileEntity* clone() const override {
        return new StunTrap(m_duration, m_cooldown.getTime(), m_pEngine);
    }

    friend class StunTrapGraphic;
    inline gfx::Graphic* createGraphic() const override {
        return new StunTrapGraphic(this);
    }

    void update(float dt) override { m_cooldown.update(dt); }
    void interact(Hero& hero) override {
        if (!m_cooldown.isComplete()) return;
        hero.stun(m_duration);
        m_cooldown.reset();
    }

private:
    Timer m_cooldown;
    float m_duration;
};