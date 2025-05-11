// definições matemáticas gerais

#pragma once

#include <cmath>

#include "vec2.hpp"

// remapping de faixas
inline double map(double value, double minX, double maxX, double minY, double maxY) {
    double spanX = maxX - minX;
    double spanY = maxY - minY;

    double percent = (value - minX) / spanX;

    return percent * spanY + minY;
}
