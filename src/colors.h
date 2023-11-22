/*---------------------------------------------------------------------------
Copyright (C), 2022-2023, Sara Echeverria (bl33h)
@author Sara Echeverria
FileName: colors.h
@version: I
Creation: 07/11/2023
Last modification: 21/11/2023
*Some parts were made using the AIs Bard and ChatGPT
------------------------------------------------------------------------------*/
#pragma once
#include <SDL.h>
#include <algorithm>
#include <iostream>

// struct representing RGBA color values.
struct Color {
    Uint8 r; // red component
    Uint8 g; // green component
    Uint8 b; // blue component
    Uint8 a; // alpha (transparency)

    // default constructor, initializes color to black with full opacity
    Color() : r(0), g(0), b(0), a(255) {}

    // constructor to set color components with optional alpha value
    Color(int red, int green, int blue, int alpha = 255) {
        r = static_cast<Uint8>(std::min(std::max(red, 0), 255));
        g = static_cast<Uint8>(std::min(std::max(green, 0), 255));
        b = static_cast<Uint8>(std::min(std::max(blue, 0), 255));
        a = static_cast<Uint8>(std::min(std::max(alpha, 0), 255));
    }

    // constructor to set color components with floating-point values, normalized to [0, 1].
    Color(float red, float green, float blue, float alpha = 1.0f) {
        r = std::clamp(static_cast<Uint8>(red * 255), Uint8(0), Uint8(255));
        g = std::clamp(static_cast<Uint8>(green * 255), Uint8(0), Uint8(255));
        b = std::clamp(static_cast<Uint8>(blue * 255), Uint8(0), Uint8(255));
        a = std::clamp(static_cast<Uint8>(alpha * 255), Uint8(0), Uint8(255));
    }

    // addition operator for combining two colors
    Color operator+(const Color& other) const {
        return Color(
                std::min(255, int(r) + int(other.r)),
                std::min(255, int(g) + int(other.g)),
                std::min(255, int(b) + int(other.b)),
                std::min(255, int(a) + int(other.a))
        );
    }

    // multiplication operator for scaling color components by a factor
    Color operator*(float factor) const {
        return Color(
                std::clamp(static_cast<Uint8>(r * factor), Uint8(0), Uint8(255)),
                std::clamp(static_cast<Uint8>(g * factor), Uint8(0), Uint8(255)),
                std::clamp(static_cast<Uint8>(b * factor), Uint8(0), Uint8(255)),
                std::clamp(static_cast<Uint8>(a * factor), Uint8(0), Uint8(255))
        );
    }

    // friend function for scaling color components by a factor from the left
    friend Color operator*(float factor, const Color& color);
};