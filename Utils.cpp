//
// Created by Yilin Zhang on 11/17/20.
//

#include "Utils.h"

std::array<float, 3> colorToRGBf(ECE_Color color)
{
    switch(color)
    {
        case ECE_Color::RED:
            return {1.f, 0.f, 0.f};
        case ECE_Color::GREEN:
            return {0.f, 1.f, 0.f};
        case ECE_Color::YELLOW:
            return {1.f, 1.f, 0.f};
        case ECE_Color::ORANGE:
            return {1.f, 165.f/255.f, 0.f};
        case ECE_Color::PINK:
            return {1.f, 192.f/255.f, 203.f/255.f};
        case ECE_Color::WHITE:
            return {1.f, 1.f, 1.f};
        case ECE_Color::SILVER:
            return {0.5f, 0.5f, 0.5f};
        case ECE_Color::GOLDEN:
            return {218.f/255.f, 165.f/255.f, 32.f/255.f};
        case ECE_Color::BLUE:
            return {0.f, 0.f, 1.f};
        case ECE_Color::BLACK:
        default:
            return {0.f, 0.f, 0.f};
    }
}

std::array<float, 2> positionToCoordinate(int x, int y)
{
    float halfGridSize = GRID_SIZE / 2.f;
    float cX = static_cast<float>(x) * GRID_SIZE;
    float cY = static_cast<float>(y) * GRID_SIZE;
    return {cX, cY};
}
