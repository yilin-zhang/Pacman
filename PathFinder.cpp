//
// Created by Yilin Zhang on 11/22/20.
//

#include "PathFinder.h"
#include <cmath>

PathFinder::PathFinder(const ECE_Map &map):map(map) {}
PathFinder::~PathFinder()= default;

void PathFinder::updateGhostDirection(const ECE_Pacman &pacman, ECE_Ghost &ghost)
{
    float pacmanX, pacmanY, ghostX, ghostY;
    pacman.getPosition(pacmanX, pacmanY);
    ghost.getPosition(ghostX, ghostY);

    int pacmanGridX, pacmanGridY, ghostGridX, ghostGridY;

    // get the positions on grid
    ghostGridX = static_cast<int>(round(ghostX));
    ghostGridY = static_cast<int>(round(ghostY));
    pacmanGridX = static_cast<int>(round(pacmanX));
    pacmanGridY = static_cast<int>(round(pacmanY));

    // get the current direction
//        auto direction = ghost->getDirection();
//        bool isNextGridValid = false;
//        switch(direction)
//        {
//            case UP:
//                isNextGridValid = map.validatePosition(ghostGridX, ghostGridY + 1);
//                break;
//            case DOWN:
//                isNextGridValid = map.validatePosition(ghostGridX, ghostGridY - 1);
//                break;
//            case LEFT:
//                isNextGridValid = map.validatePosition(ghostGridX - 1, ghostGridY);
//                break;
//            case RIGHT:
//                isNextGridValid = map.validatePosition(ghostGridX + 1, ghostGridY);
//                break;
//        }
//
//        // do not change the direction if the direction is valid
//        if (isNextGridValid)
//            return;

    // TODO: the AI is problematic
    // isFinished the horizontal potision
    if (ghostGridX == pacmanGridX)
    {
        if (pacmanGridY < ghostGridY)
        {
            // try going down first, then consider other places
            if (map.validatePosition(ghostGridX, ghostGridY - 1))
                ghost.setDirection(DOWN);
            else if (map.validatePosition(ghostGridX - 1, ghostGridY))
                ghost.setDirection(LEFT);
            else if (map.validatePosition(ghostGridX + 1, ghostGridY))
                ghost.setDirection(RIGHT);
            else if (map.validatePosition(ghostGridX, ghostGridY + 1))
                ghost.setDirection(UP);
        }
        else
        {
            if (map.validatePosition(ghostGridX, ghostGridY + 1))
                ghost.setDirection(UP);
            else if (map.validatePosition(ghostGridX - 1, ghostGridY))
                ghost.setDirection(LEFT);
            else if (map.validatePosition(ghostGridX + 1, ghostGridY))
                ghost.setDirection(RIGHT);
            else if (map.validatePosition(ghostGridX, ghostGridY - 1))
                ghost.setDirection(DOWN);
        }
    }
    else if (ghostGridX < pacmanGridX)
    {
        if (map.validatePosition(ghostGridX + 1, ghostGridY))
            ghost.setDirection(RIGHT);
        else if (map.validatePosition(ghostGridX, ghostGridY + 1))
            ghost.setDirection(UP);
        else if (map.validatePosition(ghostGridX, ghostGridY - 1))
            ghost.setDirection(DOWN);
        else if (map.validatePosition(ghostGridX - 1, ghostGridY))
            ghost.setDirection(LEFT);
    }
    else
    {
        if (map.validatePosition(ghostGridX - 1, ghostGridY))
            ghost.setDirection(LEFT);
        else if (map.validatePosition(ghostGridX, ghostGridY + 1))
            ghost.setDirection(UP);
        else if (map.validatePosition(ghostGridX, ghostGridY - 1))
            ghost.setDirection(DOWN);
        else if (map.validatePosition(ghostGridX + 1, ghostGridY))
            ghost.setDirection(RIGHT);
    }
}