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

    // display the Maze
    void display();
    bool validatePosition(int x, int y);
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

    enum ObjectType {Coin, Power, Ghost, Pacman, Path, NoPath};

    // display a half of the brick, whose length is half of the grid size
    void displayHalfBrick(int x, int y, BrickRotation rotation);

    void initializeObjects();
    void initializeWall();


    std::vector<Brick> wall;
    ECE_Color color;

    std::array<std::array<ObjectType, MAZE_COLS>, MAZE_ROWS> initialMap;
};
