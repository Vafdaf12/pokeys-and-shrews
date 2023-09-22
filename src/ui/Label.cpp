#include "Label.h"

#include "raylib.h"
#include <utility>

using namespace ui;
Label::Label(Font f, const std::string& text) : m_font(f), m_text(text) {}

Rectangle Label::getBoundingBox() const {
    Vector2 size = MeasureTextEx(m_font, m_text.c_str(), 32, 1);
    return {m_position.x, m_position.y, size.x, size.y};
}

void Label::draw() {
    if (m_background.a > 0) {
        Rectangle rect = getBoundingBox();
        DrawRectangle(rect.x, rect.y, rect.width, rect.height, m_background);
    }

    DrawTextEx(m_font, m_text.c_str(), m_position, 32, 1, m_foreground);
}