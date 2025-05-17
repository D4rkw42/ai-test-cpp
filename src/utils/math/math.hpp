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

// cálculo de distância entre dois pontos
inline double distance(double x1, double y1, double x2, double y2) {
    double dx = x2 - x1;
    double dy = y2 - y1;
    
    return std::sqrt(dx * dx + dy * dy);
}

// retorna o ângulo entre dois pontos
inline double GetAngleBetween(const Vec2& coord1, const Vec2& coord2) {
    double dx = coord2.Get(0) - coord1.Get(0);
    double dy = coord2.Get(1) - coord1.Get(1);

    return std::atan2(dy, dx);
}
