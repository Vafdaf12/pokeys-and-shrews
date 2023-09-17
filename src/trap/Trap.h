#pragma once

#include "core/Graphic.h"
#include "core/Timer.h"
#include "hero/Hero.h"

#include <stdint.h>

class Engine;

class Trap {
public:
    virtual void interact(Hero& hero) = 0;

private:
    Engine* m_pEngine;
};