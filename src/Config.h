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

#include <string>
#include <omp.h>

// NOTE: the frame rate is related to the behavior of object moving and timing
// If the frame rate is too low, the object has to move more than one unit per step, which is not allowed
// in the `move` function for now
// But if the frame rate is too high, the software can't keep the time accurate (it will be slower than the actual time)
const float FRAME_RATE = 60; // FPS
const unsigned int FRAME_TIME = static_cast<unsigned int>(1.f/FRAME_RATE*1000.f); // ms

// constant definitions
const int MAZE_ROWS = 20;
const int MAZE_COLS = 17;
const float GRID_SIZE = 1.0;

// the range threshold in which the two objects are considered touching each other
const float DISTANCE_THRESHOLD = 0.5f;
const float GHOST_RESPAWN_TIME = 5000.f; // ms
const float MIN_RESPAWN_DURATION = 2000.f; // ms
const float POWERUP_DURATION = 5000.f; // ms

const float GHOST_SPEED = 0.005f * static_cast<float>(FRAME_TIME);
const float PACMAN_SPEED = 0.007f * static_cast<float>(FRAME_TIME);

const std::string MAP_STRING = "********#********\n"
                               "o##*###*#*###*##o\n"
                               "*##*###*#*###*##*\n"
                               "*****************\n"
                               "*##*#*#####*#*##*\n"
                               "****#***#***#****\n"
                               "###*###O#O###*###\n"
                               "###*#OOOOOOO#*###\n"
                               "###*#O##G##O#*###\n"
                               "OOO*OO#OOO#OO*OOO\n"
                               "###*#O#####O#*###\n"
                               "###*#OOOOOOO#*###\n"
                               "###*#O#####O#*###\n"
                               "********#********\n"
                               "*##*###*#*###*##*\n"
                               "o*#*****@*****#*o\n"
                               "#*#*#*#####*#*#*#\n"
                               "****#***#***#****\n"
                               "*######*#*######*\n"
                               "*****************\n";



