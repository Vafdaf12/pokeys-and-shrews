#pragma once

#include "TileEntity.h"

#include "core/Engine.h"
#include "core/Timer.h"
#include "graphics/trap/TeleportTrapGraphic.h"
#include "hero/Hero.h"

class TeleportTrap : public TileEntity {
public:
    TeleportTrap(float cooldown, Engine* pEngine = nullptr)
        : TileEntity(pEngine), m_cooldown(cooldown, true) {}

    inline Graphic* createGraphic() const override {
        return new TeleportTrapGraphic(this);
    }

    void update(float dt) override { m_cooldown.update(dt); }
    void interact(Hero& hero) override {
        if (!m_cooldown.isComplete()) return;
        hero.getExplorer()->backtrack(3);
        hero.stun(1.2f);
        m_cooldown.reset();
    }

private:
    Timer m_cooldown;
};