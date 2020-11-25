//
// Created by Yilin Zhang on 11/22/20.
//

#include "PathFinder.h"
#include <cmath>

PathFinder::PathFinder(const ECE_Map &map):map(map), isChasing(true) {}
PathFinder::~PathFinder()= default;

void PathFinder::setChasing(bool isChasing)
{
    this->isChasing = isChasing;
}

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

    Direction currentDirection = ghost.getDirection();
    std::vector<Direction> availableDirections;
    std::vector<std::array<int, 2>> availablePositions;

    switch(currentDirection)
    {
        case UP:
            availableDirections = {LEFT, UP, RIGHT};
            availablePositions = {{ghostGridX-1, ghostGridY},
                                  {ghostGridX, ghostGridY+1},
                                  {ghostGridX+1, ghostGridY}};
            break;
        case DOWN:
            availableDirections = {LEFT, DOWN, RIGHT};
            availablePositions = {{ghostGridX-1, ghostGridY},
                                  {ghostGridX, ghostGridY-1},
                                  {ghostGridX+1, ghostGridY}};
            break;
        case LEFT:
            availableDirections = {LEFT, UP, DOWN};
            availablePositions = {{ghostGridX-1, ghostGridY},
                                  {ghostGridX, ghostGridY+1},
                                  {ghostGridX, ghostGridY-1}};
            break;
        case RIGHT:
            availableDirections = {RIGHT, UP, DOWN};
            availablePositions = {{ghostGridX+1, ghostGridY},
                                  {ghostGridX, ghostGridY+1},
                                  {ghostGridX, ghostGridY-1}};
            break;
    }

    Direction nextDirection = UP;
    float distance2ToCompare;
    if (isChasing)
        distance2ToCompare = 100000.f;
    else
        distance2ToCompare = 0.f;

    for (int i=0; i<3; ++i)
    {
        auto x = availablePositions[i][0];
        auto y = availablePositions[i][1];
        if (!map.validatePosition(x, y))
            continue;

        auto distance2 = static_cast<float>(pow(pacmanGridX - x, 2) + pow(pacmanGridY - y, 2));
        if ((isChasing && (distance2 < distance2ToCompare)) ||
            (!isChasing && (distance2 > distance2ToCompare)))
        {
            distance2ToCompare = distance2;
            nextDirection = availableDirections[i];
        }
    }

    ghost.setDirection(nextDirection);

}