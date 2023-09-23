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
class Button {
public:
    using ClickHandler = std::function<void()>;

    inline Button(gfx::Graphic* graphic, ClickHandler cb)
        : m_pGraphic(graphic), m_callback(cb) {}

    void update(float dt);

    inline void draw() { m_pGraphic->draw(); }

    inline gfx::Graphic* getGraphic() const { return m_pGraphic; }
    inline void onClick(ClickHandler h) { m_callback = h; }

private:
    gfx::Graphic* m_pGraphic;
    ClickHandler m_callback;
};
} // namespace ui