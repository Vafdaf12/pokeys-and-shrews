#include "Label.h"

#include "raylib.h"
#include <utility>

using namespace ui;
Label::Label(Font f, const std::string& text) : m_font(f), m_text(text) {}

Rectangle Label::getBoundingBox() const {
    Vector2 size = MeasureTextEx(m_font, m_text.c_str(), 32, 1);
    return {m_position.x, m_position.y, size.x, size.y};
}

void Label::setText(const std::string& text) { m_text = text; }
void Label::setTextColor(Color c) { m_color = c; }

void Label::draw() {
    DrawTextEx(m_font, m_text.c_str(), m_position, 32, 1, m_color);
}