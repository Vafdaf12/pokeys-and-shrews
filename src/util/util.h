#pragma once

#include "raylib.h"

#include <string>
#include <vector>

namespace util {
Rectangle inset(const Rectangle& rect, float insets);
void drawProgress(const Rectangle& bb,
    float thickness,
    float padding,
    float fac,
    Color color);

std::string trim(const std::string& str);
std::string options(
    const std::string& title, const std::vector<std::string>& opts);

int input(const std::string& prompt);
} // namespace util