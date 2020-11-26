//
// Created by Yilin Zhang on 11/17/20.
//

#pragma once
#include <array>
#include "Config.h"

enum ECE_Color
{
    BLACK,
    WHITE,
    RED,
    GREEN,
    YELLOW,
    ORANGE,
    PINK,
    BLUE,
    SILVER,
    GOLDEN
};

enum Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

/** Converts the color to it's float RGB values
 * @param color
 * @param red
 * @param green
 * @param blue
 */
void colorToRGBf(ECE_Color color, float &red, float &green, float &blue);

/** Converts the current position to the actual coordinates
 * @param x the current x position
 * @param y the current y position
 * @param cX the x value that will be used by OpenGL
 * @param cY the y value that will be used by OpenGL
 */
void positionToCoordinate(float x, float y, float &cX, float &cY);

class Timer
{
public:
    Timer();
    ~Timer();

    /** Starts the timer
     * @param ms the timer will stop after this milliseconds
     */
    void start(float ms);

    /** Updates the timer (counts one frame duration) */
    void update();

    /** Checks if the timer is finished
     * @return true if the timer is finished
     */
    bool isFinished() const;

private:
    bool isCounting; // if the counter is counting
    bool finished;   // if the counter is finished
    long counter;    // the counter
    long maxVal;     // the maximum value the the counter can be
};
