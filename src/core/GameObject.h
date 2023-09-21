#pragma once

#include "core/Graphic.h"
class Engine;

class GameObject {
public:
    inline void setEngine(Engine* pEngine) { m_pEngine = pEngine; }
    inline virtual Graphic* createGraphic() const { return nullptr; }

protected:
    inline GameObject(Engine* pEngine) : m_pEngine(pEngine) {}
    Engine* m_pEngine;
};