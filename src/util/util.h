#pragma once

#include "raylib.h"

namespace util {
Rectangle inset(const Rectangle& rect, float insets);
void drawProgress(const Rectangle& bb,
    float thickness,
    float padding,
    float fac,
    Color color);

} // namespace util