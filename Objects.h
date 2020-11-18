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
#include "Maze.h"

class ECE_Object
{
public:

    ECE_Object(ECE_Maze &maze, int x, int y, ECE_Color color);
    ECE_Object(ECE_Maze &maze);
    ~ECE_Object();

    /** Set the current position
     * @param x
     * @param y
     */
    void setPosition(int x, int y);

    /** Set the color of the object
     * @param color
     */
    void setColor(ECE_Color color);

    void move(Direction direction, int &steps);

    /** Check the validity of the given position
     * @param x
     * @param y
     * @return true if the position is valid
     */
    bool validatePosition(int x, int y);

    /** Implement this function to display on screen
     */
    virtual void display() = 0;
protected:

    /** Get the coordinate of the object according to the current position
     * @return an array of the current position
     */
    std::array<float, 2> getCoordinate() const;

    int x, y;  // the logical position on the map
    ECE_Color color;  // the color of the object
    ECE_Maze& maze;
};

class ECE_Ghost : public ECE_Object{
public:
    ECE_Ghost(ECE_Maze &maze, int x, int y, ECE_Color color);
    ECE_Ghost(ECE_Maze &maze);
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
    ECE_Pacman(ECE_Maze &maze, int x, int y);
    ECE_Pacman(ECE_Maze &maze);
    ~ECE_Pacman();
    void display() override;
};

class ECE_Coin : public ECE_Object
{
public:
    ECE_Coin(ECE_Maze &maze, int x, int y);
    ECE_Coin(ECE_Maze &maze);
    ~ECE_Coin();
    void display() override;
};

class ECE_Power : public ECE_Object
{
public:
    ECE_Power(ECE_Maze &maze, int x, int y);
    ECE_Power(ECE_Maze &maze);
    ~ECE_Power();
    void display() override;
};

