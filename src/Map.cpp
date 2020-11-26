//
// Created by Yilin Zhang on 11/18/20.
//

#include "Map.h"
#include <sstream>
#include <ctgmath>

ECE_Map::ECE_Map():
initialMap()
{
    initializeObjects();
}

ECE_Map::~ECE_Map() = default;

void ECE_Map::initializeObjects()
{
    std::stringstream ss (MAP_STRING);
    std::string line;

    for (int i=MAZE_ROWS-1; i>=0; --i)
    {
        ss >> line;
        for (int j=0; j<MAZE_COLS; ++j)
        {
            ObjectType type;
            switch(line[j])
            {
                case '*':
                    type = Coin;
                    break;
                case 'o':
                    type = Power;
                    break;
                case 'O':
                    type = Path;
                    break;
                case '@':
                    type = Pacman;
                    break;
                case 'G':
                    type = Gate;
                    break;
                case '#':
                default:
                    type = NoPath;
            }
            initialMap[i][j] = type;
        }
    }
}
bool ECE_Map::validatePosition(int x, int y) const
{
    if (x < 0 || x >= MAZE_COLS || y < 0 || y >= MAZE_ROWS)
        return false;

    // Note that the order of x and y is revered
    return  (initialMap[y][x] != NoPath) && (initialMap[y][x] != Gate);
}

bool ECE_Map::validatePosition(float x, float y) const
{
    int xFloor = floor(x);
    int xCeil = ceil(x);

    int yFloor = floor(y);
    int yCeil = ceil(y);

    return (validatePosition(xFloor, yFloor)&&
            validatePosition(xCeil, yCeil)&&
            validatePosition(xFloor, yCeil)&&
            validatePosition(xCeil, yFloor));
}

bool ECE_Map::validatePositionWhenGateOpen(int x, int y) const
{
    return (initialMap[y][x] == Gate) || validatePosition(x, y);
}

bool ECE_Map::validatePositionWhenGateOpen(float x, float y) const
{
    int xFloor = floor(x);
    int xCeil = ceil(x);

    int yFloor = floor(y);
    int yCeil = ceil(y);

    return (validatePositionWhenGateOpen(xFloor, yFloor)&&
            validatePositionWhenGateOpen(xCeil, yCeil)&&
            validatePositionWhenGateOpen(xFloor, yCeil)&&
            validatePositionWhenGateOpen(xCeil, yFloor));
}

ECE_Map::ObjectType ECE_Map::getObjectType(int x, int y) const
{
    // Note that the order of x and y is revered
    return initialMap[y][x];
}