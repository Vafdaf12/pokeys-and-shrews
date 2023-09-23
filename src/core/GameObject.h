#pragma once

#include "render/Drawable.h"
#include <stdio.h>
class Engine;

class GameObject {
public:
    virtual ~GameObject() {}
    inline void setEngine(Engine* pEngine) {
        printf("Set Engine\n");
        m_pEngine = pEngine;
    }
    inline virtual gfx::Graphic* createGraphic() const { return nullptr; }

protected:
    inline GameObject(Engine* pEngine) : m_pEngine(pEngine) {}
    Engine* m_pEngine = nullptr;
};