#pragma once

#include "core/Engine.h"
#include "core/GameObject.h"

class Hero;

class TileEntity : public GameObject {
public:
    using GameObject::GameObject;
    virtual void interact(Hero& hero) = 0;
    virtual void update(float dt) {}
};