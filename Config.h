//
// Created by Yilin Zhang on 11/17/20.
//

#pragma once

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

// constant definitions
const int MAZE_ROWS = 20;
const int MAZE_COLS = 17;
const float GRID_SIZE = 1.0;

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

