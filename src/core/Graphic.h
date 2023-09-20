#pragma once

#include "raylib.h"
#include <cassert>
#include <stdint.h>

class Graphic {
public:
    virtual ~Graphic() {}

    virtual void draw() = 0;
    virtual void update(float dt) {}

    inline void setPosition(Vector2 pos) { m_position = pos; }
    inline Vector2 getPosition() const { return m_position; }

protected:
    Vector2 m_position = {0, 0};
};