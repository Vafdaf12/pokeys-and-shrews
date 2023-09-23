#pragma once

#include "render/Drawable.h"
class Engine;

class GameObject {
public:
    virtual ~GameObject() {}
    inline void setEngine(Engine* pEngine) { m_pEngine = pEngine; }
    inline virtual gfx::Graphic* createGraphic() const { return nullptr; }

protected:
    inline GameObject(Engine* pEngine) : m_pEngine(pEngine) {}
    Engine* m_pEngine;
};