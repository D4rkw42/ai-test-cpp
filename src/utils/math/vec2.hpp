// classe para manipulação de vetores 2D

#pragma once

#include <array>

class Vec2 {
    public:
        Vec2(double a, double b) : value({ a, b }) {};
        Vec2(void) : value({ 0.0f, 0.0f }) {};

        // access
        inline double Get(int index) const {
            return this->value[index];
        }

        // mod
        inline void Set(int index, double value) {
            this->value[index] = value;
        };

        inline void operator=(const std::array<double, 2>& value) {
            Set(0, value[0]);
            Set(1, value[1]);
        }

        inline void operator=(const Vec2& vec) {
            Set(0, vec.Get(0));
            Set(1, vec.Get(1));
        }

        // basic operands
        inline Vec2 operator+(const Vec2& vec) {
            return Vec2(
                Get(0) + vec.Get(0),
                Get(1) + vec.Get(1)
            );
        }

        inline Vec2 operator-(const Vec2& vec) {
            return Vec2(
                Get(0) - vec.Get(0),
                Get(1) - vec.Get(1)
            );
        }


        inline Vec2 operator*(double value) {
            return Vec2(
                Get(0) * value,
                Get(1) * value
            );
        }

        inline Vec2 operator/(double value) {
            return Vec2(
                Get(0) / value,
                Get(1) / value
            );
        }

        // other operands
        inline void operator+=(const Vec2& vec) {
            Set(0, Get(0) + vec.Get(0));
            Set(1, Get(1) + vec.Get(1));
        }

        inline void operator-=(const Vec2& vec) {
            Set(0, Get(0) - vec.Get(0));
            Set(1, Get(1) - vec.Get(1));
        }

        inline void operator*=(double value) {
            Set(0, Get(0) * value);
            Set(1, Get(1) * value);
        }

        inline void operator/=(double value) {
            Set(0, Get(0) / value);
            Set(1, Get(1) / value);
        }

    private:
        std::array<double, 2> value;
};
