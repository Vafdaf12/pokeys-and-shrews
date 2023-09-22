#include "util.h"
#include "raylib.h"

#include <iostream>
#include <sstream>


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
std::string trim(const std::string& str) {
    size_t start = 0;
    size_t end = str.length() - 1;

    for (start = 0; start < str.length(); start++) {
        if (!isspace(str[start])) break;
    }

    for (end = str.length() - 1; end >= 0; end--) {
        if (!isspace(str[start])) break;
    }

    return str.substr(start, end - start + 1);
}

std::string options(
    const std::string& prompt, const std::vector<std::string>& opts) {
    std::stringstream stream;
    for (int i = 0; i < opts.size(); i++) {
        stream << i << ") " << opts[i] << "\n";
    }
    stream << prompt;
    return stream.str();
}
int input(const std::string& prompt) {
    int value;
    std::cout << prompt;
    std::cin >> value;
    std::cin.ignore(255, '\n');
    return value;
}
} // namespace util