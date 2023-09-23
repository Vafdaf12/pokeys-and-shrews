#pragma once
#include "render/Drawable.h"

#include "raylib.h"

#include <string>

namespace ui {
class Label : public gfx::Graphic {
public:
    Label(Font f, const std::string& text);

    virtual void draw() override;

    Rectangle getBoundingBox() const override;

    // Setters
    inline void setText(const std::string& text) { m_text = text; }
    inline void setForeground(Color c) { m_foreground = c; }
    inline void setBackground(Color c) { m_background = c; }

    // Getters
    inline const std::string& getText() const { return m_text; }

private:
    Font m_font;
    Color m_foreground = {0, 0, 0, 255};
    Color m_background = {0, 0, 0, 0};
    std::string m_text;
};

} // namespace ui