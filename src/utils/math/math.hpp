// definições matemáticas gerais

#pragma once

#include <cmath>

#include "vec2.hpp"

// definição de PI
constexpr long double PI = 3.14159265358979323846;

// remapping de faixas
inline double map(double value, double minX, double maxX, double minY, double maxY) {
    double spanX = maxX - minX;
    double spanY = maxY - minY;

    double percent = (value - minX) / spanX;

    return percent * spanY + minY;
}
