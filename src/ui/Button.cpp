#include "Button.h"

#include "raylib.h"
#include <stdio.h>

using namespace ui;

void Button::update(float dt) {
    if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) return;

    Vector2 pos = GetMousePosition();
    Rectangle rec = m_pGraphic->getBoundingBox();
    if (!CheckCollisionPointRec(pos, rec)) return;
    if (m_callback) m_callback();
}