//
// Created by Yilin Zhang on 11/25/20.
//

#pragma once

#include <array>
#include <vector>
#include "Utils.h"
#include "Map.h"

class ECE_Object
{
public:
    ECE_Object(ECE_Map &map, float x, float y, ECE_Color color);
    ~ECE_Object();

    /** Sets the current position
     * @param x
     * @param y
     */
    void setPosition(float x, float y);

    /** Assigns the x and y positions to the arguments
     * @param x
     * @param y
     */
    void getPosition(float &x, float &y) const;

    /** Sets the color of the object
     * @param color
     */
    void setColor(ECE_Color color);

    /** Implement this function to display the object on screen */
    virtual void display() = 0;
protected:

    /** Assigns the coordinate of the object according to the current position to the arguments
     * @param cX
     * @param cY
     */
    void getCoordinate(float &cX, float &cY) const;

    float x, y;  // the logical position on the map
    ECE_Color color;  // the color of the object
    ECE_Map& map;
};

class ECE_Character : public ECE_Object
{
public:
    ECE_Character(ECE_Map &map, float x, float y, ECE_Color color, float speed);
    ~ECE_Character();

    /** Moves the object (only works when distance < 1)
     * @param direction
     * @param distance
     */
    void move(Direction direction, float distance);

    /** Sets the moving status of the character
     * @param isMoving
     */
    void setMoving(bool isMoving);

    /** Checks if the status is moving
     * @return true if the object is moving
     */
    bool checkMoving() const;

    /** Sets the moving direction
     * @param direction
     */
    virtual void setDirection(Direction direction);

    /** Returns the moving direction
     * @return the current moving direction
     */
    Direction getDirection() const;

    /** Updates the position
     * @return true if the character has moved
     */
    void updatePosition();

protected:
    float speed; // the speed of the object
    bool isMoving; // if the object is moving
    Direction movingDirection; // the current moving direction
};

class ECE_Ghost : public ECE_Character{
public:
    ECE_Ghost(ECE_Map &map, float x, float y, ECE_Color color);
    ~ECE_Ghost();
    void display() override;
};

class ECE_Pacman : public ECE_Character
{
public:
    ECE_Pacman(ECE_Map &map, float x, float y);
    ~ECE_Pacman();
    void setDirection(Direction direction) override;
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

