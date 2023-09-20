#pragma once
#include "core/Graphic.h"

#include "raylib.h"

#include <string>

namespace ui {
class Label : public Graphic {
public:
    Label(Font f, const std::string& text);

    virtual void draw() override;

    // Move semantics

    Rectangle getBoundingBox() const;

    // Setters
    void setText(const std::string& text);
    void setTextColor(Color c);

    // Getters
    inline const std::string& getText() const { return m_text; }

private:
    Font m_font;
    Color m_color = {0, 0, 0, 255};
    std::string m_text;
};

} // namespace ui