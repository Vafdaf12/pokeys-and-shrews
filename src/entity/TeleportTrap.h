#pragma once

#include "TileEntity.h"

#include "core/Engine.h"
#include "core/Timer.h"
#include "hero/Hero.h"

class TeleportTrap : public TileEntity {
public:
    TeleportTrap(uint32_t cooldown, Engine* pEngine = nullptr)
        : TileEntity(pEngine), m_cooldown(cooldown, true) {}

    void update(float dt) override { m_cooldown.update(dt); }
    void interact(Hero& hero) override {
        if (!m_cooldown.isComplete()) return;
        hero.getExplorer()->backtrack(3);
        hero.stun(1200);
        m_cooldown.reset();
    }

private:
    Timer m_cooldown;
};