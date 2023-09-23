#pragma once

#include "raylib.h"
#include "render/Drawable.h"
#include "ui/Label.h"
#include <functional>
#include <memory>
#include <stdint.h>

namespace ui {

// TODO: Button is currently completely loose-standing, but it might benefit to
// implement it as a decorator
class Button : public gfx::DrawableDecorator {
public:
    using ClickHandler = std::function<void()>;

    inline Button(std::unique_ptr<gfx::Drawable> graphic, ClickHandler cb)
        : gfx::DrawableDecorator(std::move(graphic)), m_callback(cb) {}

    void update(float dt);

    inline void onClick(ClickHandler h) { m_callback = h; }

private:
    ClickHandler m_callback;
};
} // namespace ui