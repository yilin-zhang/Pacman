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

class ECE_Object
{
public:
    ECE_Object(int x, int y, ECE_Color color);
    ECE_Object();
    ~ECE_Object();

    // position setter
    void setPosition(int x, int y);

    // color setter
    void setColor(ECE_Color color);

    // implement this function to display the object
    virtual void display() = 0;
protected:

    // get the coordinate of the object according to the current position
    std::array<float, 2> getCoordinate() const;
    int x, y;  // the logical position on the map
    ECE_Color color;  // the color of the object
};

class ECE_Ghost : public ECE_Object{
public:
    ECE_Ghost(int x, int y, ECE_Color color);
    ECE_Ghost();
    ~ECE_Ghost();
    void display() override;

    // display the object at coordinate (cX, cY)
    void display(float cX, float cY);
};

class ECE_Pacman : public ECE_Object
{
public:
    ECE_Pacman(int x, int y);
    ECE_Pacman();
    ~ECE_Pacman();
    void display() override;
};

class ECE_Coin : public ECE_Object
{
public:
    ECE_Coin(int x, int y);
    ECE_Coin();
    ~ECE_Coin();
    void display() override;
};

class ECE_Power : public ECE_Object
{
public:
    ECE_Power(int x, int y);
    ECE_Power();
    ~ECE_Power();
    void display() override;
};

