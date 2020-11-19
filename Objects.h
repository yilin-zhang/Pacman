/*
Author: Yilin Zhang
Class: ECE6122
Last Date Modified: 10/24/2020
Description:
Class declarations and constant definitions
*/

#pragma once

#include <array>
#include <vector>
#include "Config.h"
#include "Map.h"

class ECE_Object
{
public:
    ECE_Object(ECE_Map &map, float x, float y, ECE_Color color);
    ~ECE_Object();

    /** Set the current position
     * @param x
     * @param y
     */
    void setPosition(float x, float y);

    void getPosition(float &x, float &y) const;

    /** Set the color of the object
     * @param color
     */
    void setColor(ECE_Color color);

    /** Move the object (only works when distance < 1)
     * @param direction
     * @param distance
     */
    void move(Direction direction, float distance);

    /** Implement this function to display on screen
     */
    virtual void display() = 0;
protected:

    /** Get the coordinate of the object according to the current position
     *
     * @param cX
     * @param cY
     */
    void getCoordinate(float &cX, float &cY) const;

    float x, y;  // the logical position on the map
    ECE_Color color;  // the color of the object
    ECE_Map& map;
};

class ECE_Ghost : public ECE_Object{
public:
    ECE_Ghost(ECE_Map &map, float x, float y, ECE_Color color);
    ~ECE_Ghost();
    void display() override;

    /** An additional function to specify the coordinate to display
     * @param cX
     * @param cY
     */
    void display(float cX, float cY);
};

class ECE_Pacman : public ECE_Object
{
public:
    ECE_Pacman(ECE_Map &map, float x, float y);
    ~ECE_Pacman();
    void display() override;
};

class ECE_Coin : public ECE_Object
{
public:
    ECE_Coin(ECE_Map &map, float x, float y);
    ~ECE_Coin();
    void display() override;
};

class ECE_Power : public ECE_Object
{
public:
    ECE_Power(ECE_Map &map, float x, float y);
    ~ECE_Power();
    void display() override;
};

