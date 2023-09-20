#pragma once

#include "core/Engine.h"

class Hero;

class TileEntity {
public:
    virtual void interact(Hero& hero) = 0;
    virtual void update(float dt) {}

    inline void setEngine(Engine* pEngine) { m_pEngine = pEngine; }

protected:
    TileEntity(Engine* pEngine) : m_pEngine(pEngine) {}
    Engine* m_pEngine;
};