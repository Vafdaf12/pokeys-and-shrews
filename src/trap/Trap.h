#pragma once

#include "core/Graphic.h"
#include "core/Timer.h"

#include <stdint.h>

class Engine;
class Hero;

class Trap {
public:
    virtual void interact(Hero& hero) = 0;

    inline void setEngine(Engine* engine) { m_pEngine = engine; }

protected:
    Engine* m_pEngine;
};