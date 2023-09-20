#include "Button.h"

#include "raylib.h"
#include <stdio.h>

using namespace ui;

Button::Button(Font font, const std::string& text, ClickHandler cb)
    : Label(font, text), m_onClick(cb) {}

void Button::draw() {
    DrawRectangleRec(getBoundingBox(), m_background);
    Label::draw();
}
void Button::update(uint32_t dt) {
    if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) return;

    Vector2 pos = GetMousePosition();
    Rectangle rec = getBoundingBox();
    if (!CheckCollisionPointRec(pos, rec)) return;
    if (m_onClick) m_onClick();
}