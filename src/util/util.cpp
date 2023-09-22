#include "util.h"
#include "raylib.h"

namespace util {
Rectangle inset(const Rectangle& r, float insets) {
    return {
        r.x - insets,
        r.y - insets,
        r.width + 2 * insets,
        r.height + 2 * insets,
    };
}
void drawProgress(const Rectangle& bb,
    float thickness,
    float padding,
    float fac,
    Color color) {

    float x = bb.x + padding;
    float y = bb.y + bb.height - padding - thickness;
    float width = bb.width - 2 * padding;

    DrawRectangleRec({x, y, width, thickness}, BLACK);
    DrawRectangleRec({x, y, width * fac, thickness}, color);
}
} // namespace util