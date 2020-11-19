//
// Created by Yilin Zhang on 11/17/20.
//

#include <fstream>
#include <iostream>
#include "Maze.h"
#include "Utils.h"

ECE_Maze::ECE_Maze()
{
    initializeWall();
}

ECE_Maze::~ECE_Maze(){}

void ECE_Maze::display()
{
    // get color
    auto colorRGB = colorToRGBf(color);
    float colorR = colorRGB[0];
    float colorG = colorRGB[1];
    float colorB = colorRGB[2];
    glColor3f(colorR, colorG, colorB);

    auto quadratic = gluNewQuadric();

    for (auto &brick : wall)
    {
        auto coordinate = positionToCoordinate(brick.x, brick.y);
        auto x = coordinate[0];
        auto y = coordinate[1];


        switch(brick.type)
        {
            case BrickType::I:
                switch(brick.rotation)
                {
                    case BrickRotation::Up:
                    case BrickRotation::Down:
                        displayHalfBrick(x, y, BrickRotation::Up);
                        displayHalfBrick(x, y, BrickRotation::Down);
                        break;
                    case BrickRotation::Left:
                    case BrickRotation::Right:
                        displayHalfBrick(x, y, BrickRotation::Left);
                        displayHalfBrick(x, y, BrickRotation::Right);
                        break;

                }
                break;
            case BrickType::L:
                // draw the vertical bar
                switch(brick.rotation)
                {
                    case BrickRotation::Up:
                        displayHalfBrick(x, y, BrickRotation::Up);
                        displayHalfBrick(x, y, BrickRotation::Right);
                        break;
                    case BrickRotation::Down:
                        displayHalfBrick(x, y, BrickRotation::Left);
                        displayHalfBrick(x, y, BrickRotation::Down);
                        break;
                    case BrickRotation::Left:
                        displayHalfBrick(x, y, BrickRotation::Left);
                        displayHalfBrick(x, y, BrickRotation::Up);
                        break;
                    case BrickRotation::Right:
                        displayHalfBrick(x, y, BrickRotation::Right);
                        displayHalfBrick(x, y, BrickRotation::Down);
                        break;
                }
                break;
            case BrickType::T:
                // draw the long horizontal bar
                switch(brick.rotation)
                {
                    case BrickRotation::Up:
                        displayHalfBrick(x, y, BrickRotation::Down);
                        displayHalfBrick(x, y, BrickRotation::Left);
                        displayHalfBrick(x, y, BrickRotation::Right);
                        break;
                    case BrickRotation::Down:
                        displayHalfBrick(x, y, BrickRotation::Up);
                        displayHalfBrick(x, y, BrickRotation::Left);
                        displayHalfBrick(x, y, BrickRotation::Right);
                        break;
                    case BrickRotation::Left:
                        displayHalfBrick(x, y, BrickRotation::Up);
                        displayHalfBrick(x, y, BrickRotation::Down);
                        displayHalfBrick(x, y, BrickRotation::Right);
                        break;
                    case BrickRotation::Right:
                        displayHalfBrick(x, y, BrickRotation::Up);
                        displayHalfBrick(x, y, BrickRotation::Down);
                        displayHalfBrick(x, y, BrickRotation::Left);
                        break;
                }
                break;
            case BrickType::i:
                switch(brick.rotation)
                {
                    case BrickRotation::Up:
                        displayHalfBrick(x, y, BrickRotation::Up);
                        break;
                    case BrickRotation::Down:
                        displayHalfBrick(x, y, BrickRotation::Down);
                        break;
                    case BrickRotation::Left:
                        displayHalfBrick(x, y, BrickRotation::Left);
                        break;
                    case BrickRotation::Right:
                        displayHalfBrick(x, y, BrickRotation::Right);
                        break;
                }
                break;
        }
    }
}

void ECE_Maze::displayHalfBrick(int x, int y, BrickRotation rotation)
{
    auto quadratic = gluNewQuadric();
    auto coordinate = positionToCoordinate(x, y);
    glPushMatrix();
    switch (rotation)
    {
        case BrickRotation::Up:
            glTranslatef(coordinate[0], coordinate[1]+GRID_SIZE/4.f, 0.0);
            glTranslatef(0.0, GRID_SIZE/4.f, 0.0);
            glRotatef(90, 1.0, 0.0, 0.0);
            break;
        case BrickRotation::Down:
            glTranslatef(coordinate[0], coordinate[1]-GRID_SIZE/4.f, 0.0);
            glTranslatef(0.0, GRID_SIZE/4.f, 0.0);
            glRotatef(90, 1.0, 0.0, 0.0);
            break;
        case BrickRotation::Left:
            glTranslatef(coordinate[0]-GRID_SIZE/4.f, coordinate[1], 0.0);
            glTranslatef(-GRID_SIZE/4.f, 0.0, 0.0);
            glRotatef(90, 0.0, 1.0, 0.0);
            break;
        case BrickRotation::Right:
            glTranslatef(coordinate[0]+GRID_SIZE/4.f, coordinate[1], 0.0);
            glTranslatef(-GRID_SIZE/4.f, 0.0, 0.0);
            glRotatef(90, 0.0, 1.0, 0.0);
            break;
    }
    gluCylinder(quadratic, GRID_SIZE/7.f, GRID_SIZE/7.f, GRID_SIZE/2.f, 10, 8);
    glPopMatrix();

}

void ECE_Maze::initializeWall()
{
    // initialize the wall (this is a bad idea, but it works, at least for now)
    wall.push_back(Brick{-1, -1,  BrickType::L, BrickRotation::Up});
    wall.push_back(Brick{-1,  0,  BrickType::I, BrickRotation::Up});
    wall.push_back(Brick{-1,  1,  BrickType::I, BrickRotation::Up});
    wall.push_back(Brick{-1,  2,  BrickType::I, BrickRotation::Up});
    wall.push_back(Brick{-1,  3,  BrickType::T, BrickRotation::Left});
    wall.push_back(Brick{-1,  4,  BrickType::I, BrickRotation::Up});
    wall.push_back(Brick{-1,  5,  BrickType::I, BrickRotation::Up});
    wall.push_back(Brick{-1,  6,  BrickType::I, BrickRotation::Up});
    wall.push_back(Brick{-1,  7,  BrickType::L, BrickRotation::Right});
    wall.push_back(Brick{-1,  9,  BrickType::i, BrickRotation::Right});
    wall.push_back(Brick{-1,  11, BrickType::i, BrickRotation::Right});
    wall.push_back(Brick{-1,  13, BrickType::L, BrickRotation::Up});
    wall.push_back(Brick{-1,  14, BrickType::I, BrickRotation::Up});
    wall.push_back(Brick{-1,  15, BrickType::I, BrickRotation::Up});
    wall.push_back(Brick{-1,  16, BrickType::I, BrickRotation::Up});
    wall.push_back(Brick{-1,  17, BrickType::I, BrickRotation::Up});
    wall.push_back(Brick{-1,  18, BrickType::I, BrickRotation::Up});
    wall.push_back(Brick{-1,  19, BrickType::I, BrickRotation::Up});
    wall.push_back(Brick{-1,  20, BrickType::L, BrickRotation::Right});

    wall.push_back(Brick{17, -1,  BrickType::L, BrickRotation::Left});
    wall.push_back(Brick{17,  0,  BrickType::I, BrickRotation::Up});
    wall.push_back(Brick{17,  1,  BrickType::I, BrickRotation::Up});
    wall.push_back(Brick{17,  2,  BrickType::I, BrickRotation::Up});
    wall.push_back(Brick{17,  3,  BrickType::T, BrickRotation::Right});
    wall.push_back(Brick{17,  4,  BrickType::I, BrickRotation::Up});
    wall.push_back(Brick{17,  5,  BrickType::I, BrickRotation::Up});
    wall.push_back(Brick{17,  6,  BrickType::I, BrickRotation::Up});
    wall.push_back(Brick{17,  7,  BrickType::L, BrickRotation::Down});
    wall.push_back(Brick{17,  9,  BrickType::i, BrickRotation::Left});
    wall.push_back(Brick{17,  11, BrickType::i, BrickRotation::Left});
    wall.push_back(Brick{17,  13, BrickType::L, BrickRotation::Left});
    wall.push_back(Brick{17,  14, BrickType::I, BrickRotation::Up});
    wall.push_back(Brick{17,  15, BrickType::I, BrickRotation::Up});
    wall.push_back(Brick{17,  16, BrickType::I, BrickRotation::Up});
    wall.push_back(Brick{17,  17, BrickType::I, BrickRotation::Up});
    wall.push_back(Brick{17,  18, BrickType::I, BrickRotation::Up});
    wall.push_back(Brick{17,  19, BrickType::I, BrickRotation::Up});
    wall.push_back(Brick{17,  20, BrickType::L, BrickRotation::Down});

    wall.push_back(Brick{0,   -1, BrickType::I, BrickRotation::Right});
    wall.push_back(Brick{0,    3, BrickType::I, BrickRotation::Right});
    wall.push_back(Brick{0,    7, BrickType::I, BrickRotation::Right});
    wall.push_back(Brick{0,    9, BrickType::I, BrickRotation::Right});
    wall.push_back(Brick{0,   11, BrickType::I, BrickRotation::Right});
    wall.push_back(Brick{0,   13, BrickType::I, BrickRotation::Right});
    wall.push_back(Brick{0,   20, BrickType::I, BrickRotation::Right});

    wall.push_back(Brick{16,  -1, BrickType::I, BrickRotation::Left});
    wall.push_back(Brick{16,   3, BrickType::I, BrickRotation::Left});
    wall.push_back(Brick{16,   7, BrickType::I, BrickRotation::Left});
    wall.push_back(Brick{16,   9, BrickType::I, BrickRotation::Left});
    wall.push_back(Brick{16,  11, BrickType::I, BrickRotation::Left});
    wall.push_back(Brick{16,  13, BrickType::I, BrickRotation::Left});
    wall.push_back(Brick{16,  20, BrickType::I, BrickRotation::Left});

    wall.push_back(Brick{1,   -1, BrickType::I, BrickRotation::Right});
    wall.push_back(Brick{1,    1, BrickType::i, BrickRotation::Right});
    wall.push_back(Brick{1,    5, BrickType::i, BrickRotation::Right});
    wall.push_back(Brick{1,    7, BrickType::I, BrickRotation::Right});
    wall.push_back(Brick{1,    9, BrickType::I, BrickRotation::Right});
    wall.push_back(Brick{1,   11, BrickType::I, BrickRotation::Right});
    wall.push_back(Brick{1,   13, BrickType::I, BrickRotation::Right});
    wall.push_back(Brick{1,   15, BrickType::i, BrickRotation::Right});
    wall.push_back(Brick{1,   17, BrickType::L, BrickRotation::Up});
    wall.push_back(Brick{1,   18, BrickType::L, BrickRotation::Right});
    wall.push_back(Brick{1,   20, BrickType::I, BrickRotation::Right});

    wall.push_back(Brick{15,  -1, BrickType::I, BrickRotation::Left});
    wall.push_back(Brick{15,   1, BrickType::i, BrickRotation::Left});
    wall.push_back(Brick{15,   5, BrickType::i, BrickRotation::Left});
    wall.push_back(Brick{15,   7, BrickType::I, BrickRotation::Left});
    wall.push_back(Brick{15,   9, BrickType::I, BrickRotation::Left});
    wall.push_back(Brick{15,  11, BrickType::I, BrickRotation::Left});
    wall.push_back(Brick{15,  13, BrickType::I, BrickRotation::Left});
    wall.push_back(Brick{15,  15, BrickType::i, BrickRotation::Left});
    wall.push_back(Brick{15,  17, BrickType::L, BrickRotation::Left});
    wall.push_back(Brick{15,  18, BrickType::L, BrickRotation::Down});
    wall.push_back(Brick{15,  20, BrickType::I, BrickRotation::Left});

    wall.push_back(Brick{2,   -1, BrickType::I, BrickRotation::Right});
    wall.push_back(Brick{2,    1, BrickType::I, BrickRotation::Right});
    wall.push_back(Brick{2,    3, BrickType::i, BrickRotation::Up});
    wall.push_back(Brick{2,    4, BrickType::I, BrickRotation::Up});
    wall.push_back(Brick{2,    5, BrickType::L, BrickRotation::Down});
    wall.push_back(Brick{2,    7, BrickType::L, BrickRotation::Left});
    wall.push_back(Brick{2,    8, BrickType::I, BrickRotation::Up});
    wall.push_back(Brick{2,    9, BrickType::L, BrickRotation::Down});
    wall.push_back(Brick{2,   11, BrickType::L, BrickRotation::Left});
    wall.push_back(Brick{2,   12, BrickType::I, BrickRotation::Up});
    wall.push_back(Brick{2,   13, BrickType::L, BrickRotation::Down});
    wall.push_back(Brick{2,   15, BrickType::i, BrickRotation::Left});
    wall.push_back(Brick{2,   17, BrickType::L, BrickRotation::Left});
    wall.push_back(Brick{2,   18, BrickType::L, BrickRotation::Down});
    wall.push_back(Brick{2,   20, BrickType::I, BrickRotation::Right});

    wall.push_back(Brick{14,  -1, BrickType::I, BrickRotation::Left});
    wall.push_back(Brick{14,   1, BrickType::I, BrickRotation::Left});
    wall.push_back(Brick{14,   3, BrickType::i, BrickRotation::Up});
    wall.push_back(Brick{14,   4, BrickType::I, BrickRotation::Up});
    wall.push_back(Brick{14,   5, BrickType::L, BrickRotation::Right});
    wall.push_back(Brick{14,   7, BrickType::L, BrickRotation::Up});
    wall.push_back(Brick{14,   8, BrickType::I, BrickRotation::Up});
    wall.push_back(Brick{14,   9, BrickType::L, BrickRotation::Right});
    wall.push_back(Brick{14,  11, BrickType::L, BrickRotation::Up});
    wall.push_back(Brick{14,  12, BrickType::I, BrickRotation::Up});
    wall.push_back(Brick{14,  13, BrickType::L, BrickRotation::Right});
    wall.push_back(Brick{14,  15, BrickType::i, BrickRotation::Right});
    wall.push_back(Brick{14,  17, BrickType::L, BrickRotation::Up});
    wall.push_back(Brick{14,  18, BrickType::L, BrickRotation::Right});
    wall.push_back(Brick{14,  20, BrickType::I, BrickRotation::Left});

    wall.push_back(Brick{3,   -1, BrickType::I, BrickRotation::Right});
    wall.push_back(Brick{3,    1, BrickType::I, BrickRotation::Right});
    wall.push_back(Brick{3,   20, BrickType::I, BrickRotation::Right});

    wall.push_back(Brick{13,  -1, BrickType::I, BrickRotation::Left});
    wall.push_back(Brick{13,   1, BrickType::I, BrickRotation::Left});
    wall.push_back(Brick{13,  20, BrickType::I, BrickRotation::Left});

    wall.push_back(Brick{4,   -1, BrickType::I, BrickRotation::Right});
    wall.push_back(Brick{4,    1, BrickType::T, BrickRotation::Down});
    wall.push_back(Brick{4,    2, BrickType::I, BrickRotation::Up});
    wall.push_back(Brick{4,    3, BrickType::i, BrickRotation::Down});
    wall.push_back(Brick{4,    5, BrickType::i, BrickRotation::Right});
    wall.push_back(Brick{4,    7, BrickType::i, BrickRotation::Up});
    wall.push_back(Brick{4,    8, BrickType::I, BrickRotation::Up});
    wall.push_back(Brick{4,    9, BrickType::i, BrickRotation::Down});
    wall.push_back(Brick{4,   11, BrickType::i, BrickRotation::Up});
    wall.push_back(Brick{4,   12, BrickType::I, BrickRotation::Up});
    wall.push_back(Brick{4,   13, BrickType::T, BrickRotation::Left});
    wall.push_back(Brick{4,   14, BrickType::I, BrickRotation::Up});
    wall.push_back(Brick{4,   15, BrickType::i, BrickRotation::Down});
    wall.push_back(Brick{4,   17, BrickType::L, BrickRotation::Up});
    wall.push_back(Brick{4,   18, BrickType::L, BrickRotation::Right});
    wall.push_back(Brick{4,   20, BrickType::I, BrickRotation::Right});

    wall.push_back(Brick{12,  -1, BrickType::I, BrickRotation::Right});
    wall.push_back(Brick{12,   1, BrickType::T, BrickRotation::Down});
    wall.push_back(Brick{12,   2, BrickType::I, BrickRotation::Up});
    wall.push_back(Brick{12,   3, BrickType::i, BrickRotation::Down});
    wall.push_back(Brick{12,   5, BrickType::i, BrickRotation::Left});
    wall.push_back(Brick{12,   7, BrickType::i, BrickRotation::Up});
    wall.push_back(Brick{12,   8, BrickType::I, BrickRotation::Up});
    wall.push_back(Brick{12,   9, BrickType::i, BrickRotation::Down});
    wall.push_back(Brick{12,  11, BrickType::i, BrickRotation::Up});
    wall.push_back(Brick{12,  12, BrickType::I, BrickRotation::Up});
    wall.push_back(Brick{12,  13, BrickType::T, BrickRotation::Right});
    wall.push_back(Brick{12,  14, BrickType::I, BrickRotation::Up});
    wall.push_back(Brick{12,  15, BrickType::i, BrickRotation::Down});
    wall.push_back(Brick{12,  17, BrickType::L, BrickRotation::Left});
    wall.push_back(Brick{12,  18, BrickType::L, BrickRotation::Down});
    wall.push_back(Brick{12,  20, BrickType::I, BrickRotation::Left});

    wall.push_back(Brick{5,   -1, BrickType::I, BrickRotation::Right});
    wall.push_back(Brick{5,    1, BrickType::I, BrickRotation::Right});
    wall.push_back(Brick{5,    5, BrickType::I, BrickRotation::Right});
    wall.push_back(Brick{5,   13, BrickType::I, BrickRotation::Right});
    wall.push_back(Brick{5,   17, BrickType::I, BrickRotation::Right});
    wall.push_back(Brick{5,   18, BrickType::I, BrickRotation::Right});
    wall.push_back(Brick{5,   20, BrickType::I, BrickRotation::Right});

    wall.push_back(Brick{11,  -1, BrickType::I, BrickRotation::Left});
    wall.push_back(Brick{11,   1, BrickType::I, BrickRotation::Left});
    wall.push_back(Brick{11,   5, BrickType::I, BrickRotation::Left});
    wall.push_back(Brick{11,  13, BrickType::I, BrickRotation::Left});
    wall.push_back(Brick{11,  17, BrickType::I, BrickRotation::Left});
    wall.push_back(Brick{11,  18, BrickType::I, BrickRotation::Left});
    wall.push_back(Brick{11,  20, BrickType::I, BrickRotation::Left});

    wall.push_back(Brick{6,   -1, BrickType::I, BrickRotation::Right});
    wall.push_back(Brick{6,    1, BrickType::i, BrickRotation::Left});
    wall.push_back(Brick{6,    3, BrickType::i, BrickRotation::Right});
    wall.push_back(Brick{6,    5, BrickType::i, BrickRotation::Left});
    wall.push_back(Brick{6,    7, BrickType::i, BrickRotation::Right});
    wall.push_back(Brick{6,    9, BrickType::L, BrickRotation::Up});
    wall.push_back(Brick{6,   10, BrickType::I, BrickRotation::Up});
    wall.push_back(Brick{6,   11, BrickType::L, BrickRotation::Right});
    wall.push_back(Brick{6,   13, BrickType::i, BrickRotation::Left});
    wall.push_back(Brick{6,   15, BrickType::i, BrickRotation::Right});
    wall.push_back(Brick{6,   17, BrickType::L, BrickRotation::Left});
    wall.push_back(Brick{6,   18, BrickType::L, BrickRotation::Down});
    wall.push_back(Brick{6,   20, BrickType::I, BrickRotation::Right});

    wall.push_back(Brick{10,  -1, BrickType::I, BrickRotation::Right});
    wall.push_back(Brick{10,   1, BrickType::i, BrickRotation::Right});
    wall.push_back(Brick{10,   3, BrickType::i, BrickRotation::Left});
    wall.push_back(Brick{10,   5, BrickType::i, BrickRotation::Right});
    wall.push_back(Brick{10,   7, BrickType::i, BrickRotation::Left});
    wall.push_back(Brick{10,   9, BrickType::L, BrickRotation::Left});
    wall.push_back(Brick{10,  10, BrickType::I, BrickRotation::Up});
    wall.push_back(Brick{10,  11, BrickType::L, BrickRotation::Down});
    wall.push_back(Brick{10,  13, BrickType::i, BrickRotation::Right});
    wall.push_back(Brick{10,  15, BrickType::i, BrickRotation::Left});
    wall.push_back(Brick{10,  17, BrickType::L, BrickRotation::Up});
    wall.push_back(Brick{10,  18, BrickType::L, BrickRotation::Right});
    wall.push_back(Brick{10,  20, BrickType::I, BrickRotation::Left});

    wall.push_back(Brick{7,   -1, BrickType::I, BrickRotation::Right});
    wall.push_back(Brick{7,    3, BrickType::I, BrickRotation::Right});
    wall.push_back(Brick{7,    7, BrickType::I, BrickRotation::Right});
    wall.push_back(Brick{7,    9, BrickType::I, BrickRotation::Right});
    wall.push_back(Brick{7,   11, BrickType::I, BrickRotation::Right});
    wall.push_back(Brick{7,   15, BrickType::I, BrickRotation::Right});
    wall.push_back(Brick{7,   20, BrickType::I, BrickRotation::Right});

    wall.push_back(Brick{9,   -1, BrickType::I, BrickRotation::Left});
    wall.push_back(Brick{9,    3, BrickType::I, BrickRotation::Left});
    wall.push_back(Brick{9,    7, BrickType::I, BrickRotation::Left});
    wall.push_back(Brick{9,    9, BrickType::I, BrickRotation::Left});
    wall.push_back(Brick{9,   11, BrickType::I, BrickRotation::Left});
    wall.push_back(Brick{9,   15, BrickType::I, BrickRotation::Left});
    wall.push_back(Brick{9,   20, BrickType::I, BrickRotation::Left});

    wall.push_back(Brick{8,   -1, BrickType::I, BrickRotation::Left});
    wall.push_back(Brick{8,    1, BrickType::i, BrickRotation::Up});
    wall.push_back(Brick{8,    2, BrickType::I, BrickRotation::Up});
    wall.push_back(Brick{8,    3, BrickType::T, BrickRotation::Up});
    wall.push_back(Brick{8,    5, BrickType::i, BrickRotation::Up});
    wall.push_back(Brick{8,    6, BrickType::I, BrickRotation::Up});
    wall.push_back(Brick{8,    7, BrickType::T, BrickRotation::Up});
    wall.push_back(Brick{8,    9, BrickType::I, BrickRotation::Right});
    wall.push_back(Brick{8,   11, BrickType::I, BrickRotation::Right});
    wall.push_back(Brick{8,   13, BrickType::i, BrickRotation::Up});
    wall.push_back(Brick{8,   14, BrickType::I, BrickRotation::Up});
    wall.push_back(Brick{8,   15, BrickType::T, BrickRotation::Up});
    wall.push_back(Brick{8,   17, BrickType::i, BrickRotation::Up});
    wall.push_back(Brick{8,   18, BrickType::I, BrickRotation::Up});
    wall.push_back(Brick{8,   19, BrickType::I, BrickRotation::Up});
    wall.push_back(Brick{8,   20, BrickType::T, BrickRotation::Up});

    color = ECE_Color::BLUE;
}