//
// Created by Yilin Zhang on 11/17/20.
//

#include "Utils.h"
#include <iostream>

void colorToRGBf(ECE_Color color, float &red, float &green, float &blue)
{
    switch(color)
    {
        case ECE_Color::RED:
            red = 1.f;
            green = 0.f;
            blue = 0.f;
            break;
        case ECE_Color::GREEN:
            red = 0.f;
            green = 1.f;
            blue = 0.f;
            break;
        case ECE_Color::YELLOW:
            red = 1.f;
            green = 1.f;
            blue = 0.f;
            break;
        case ECE_Color::ORANGE:
            red = 1.f;
            green = 165.f/255.f;
            blue = 0.f;
            break;
        case ECE_Color::PINK:
            red = 1.f;
            green = 192.f/255.f;
            blue = 203.f/255.f;
            break;
        case ECE_Color::WHITE:
            red = 1.f;
            green = 1.f;
            blue = 1.f;
            break;
        case ECE_Color::SILVER:
            red = 0.5f;
            green = 0.5f;
            blue = 0.5f;
            break;
        case ECE_Color::GOLDEN:
            red = 218.f/255.f;
            green = 165.f/255.f;
            blue = 32.f/255.f;
            break;
        case ECE_Color::BLUE:
            red = 0.f;
            green = 0.f;
            blue = 1.f;
            break;
        case ECE_Color::BLACK:
        default:
            red = 0.f;
            green = 0.f;
            blue = 1.f;
    }
}

void positionToCoordinate(float x, float y, float &cX, float &cY)
{
    float halfGridSize = GRID_SIZE / 2.f;
    cX = x * GRID_SIZE;
    cY = y * GRID_SIZE;
}


//////////////////////////////////////////////////
/// Timer
//////////////////////////////////////////////////

Timer::Timer():isCounting(false), finished(false), counter(0), maxVal(0) {}
Timer::~Timer()= default;

void Timer::start(float ms)
{
    maxVal = static_cast<long>(ms / static_cast<float>(FRAME_TIME));
    counter = 0;
    isCounting = true;
    finished = false;
    std::cout << "maxVal: " << maxVal << std::endl;
}

void Timer::update()
{
    if (!isCounting)
        return;

    if (++counter >= maxVal)
    {
        isCounting = false;
        finished = true;
    }
}

bool Timer::check()
{
    return finished;
}
