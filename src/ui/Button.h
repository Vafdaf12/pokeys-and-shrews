#pragma once

#include "raylib.h"
#include "ui/Label.h"
#include <functional>
#include <stdint.h>

namespace ui {
class Button : public Label {
public:
    using ClickHandler = std::function<void()>;

    Button(Font font, const std::string& text, ClickHandler cb);

    void draw() override;
    void update(float dt) override;

    inline void setBackground(Color c) { m_background = c; }
    inline void onClick(ClickHandler h) { m_onClick = h; }

private:
    Color m_background;
    ClickHandler m_onClick;
};
} // namespace ui