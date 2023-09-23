#pragma once

#include <memory>

#include "raylib.h"

namespace gfx {
using Rect = Rectangle;
using Vec2 = Vector2;
using Tex2D = Texture2D;

class Drawable {
public:
    virtual ~Drawable() {}

    /**
     * Draws the object (does not support multiple draw outputs)
     */
    virtual void draw() = 0;

    /**
     * Updates temporal features of element (e.g. animating a spritesheet)
     */
    virtual void update(float dt) {}

    virtual Rect getBoundingBox() const = 0;
};

class Graphic : public Drawable {
public:
    inline void setPosition(Vector2 pos) { m_position = pos; }
    inline Vector2 getPosition() const { return m_position; }

protected:
    Vec2 m_position = {0, 0};
};

class DrawableDecorator : public Drawable {
public:
    inline virtual void draw() override { _pInternal->draw(); }
    inline virtual void update(float dt) override { _pInternal->update(dt); }
    inline virtual Rect getBoundingBox() const override {
        return _pInternal->getBoundingBox();
    };

    inline Drawable* getInternal() const { return _pInternal.get(); }

protected:
    inline DrawableDecorator(std::unique_ptr<Drawable> internal)
        : _pInternal(std::move(internal)) {}

    std::unique_ptr<Drawable> _pInternal;
};

} // namespace gfx