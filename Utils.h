//
// Created by Yilin Zhang on 11/17/20.
//

#pragma once
#include <array>
#include "Config.h"

/** Convert the color to it's float RGB values
 * @param color
 * @param red
 * @param green
 * @param blue
 */
void colorToRGBf(ECE_Color color, float &red, float &green, float &blue);

/** Convert the current position to the actual coordinates
 * @param x
 * @param y
 * @param cX
 * @param cY
 */
void positionToCoordinate(float x, float y, float &cX, float &cY);

class Timer
{
public:
    Timer();
    ~Timer();
    void start(float ms);
    void update();
    bool check();
private:
    bool isCounting;
    bool finished;
    long counter;
    long maxVal;
};
