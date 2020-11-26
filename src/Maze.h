//
// Created by Yilin Zhang on 11/17/20.
//

#pragma once
#include <vector>
#include <array>
#include "Utils.h"


class ECE_Maze
{
public:
    ECE_Maze();
    ~ECE_Maze();

    /** Displays the maze */
    void display();

private:
    enum BrickType {I, T, L, i};
    enum BrickRotation {Up, Down, Left, Right};
    struct Brick
    {
        int x;
        int y;
        BrickType type;
        BrickRotation rotation;
    };

    /** Displays a half of the brick, whose length is half of the grid size
     * @param x the x position
     * @param y the y position
     * @param rotation the rotation type
     */
    void displayHalfBrick(int x, int y, BrickRotation rotation);

    /** Initializes all the wall bricks of the maze */
    void initializeWall();

    std::vector<Brick> wall; // stores all the bricks
    ECE_Color color;         // the color of the maze
};
