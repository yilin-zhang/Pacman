//
// Created by Yilin Zhang on 11/17/20.
//

#pragma once
#include <vector>
#include <array>
#include "Config.h"


class ECE_Maze
{
public:
    ECE_Maze();
    ~ECE_Maze();

    /** Display the maze
     */
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

    // display a half of the brick, whose length is half of the grid size
    void displayHalfBrick(int x, int y, BrickRotation rotation);

    void initializeWall();

    std::vector<Brick> wall;
    ECE_Color color;
};
