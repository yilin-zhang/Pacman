//
// Created by Yilin Zhang on 11/18/20.
//

#include "Map.h"
#include <fstream>
#include <ctgmath>

ECE_Map::ECE_Map():
initialMap()
{
    initializeObjects();
}

ECE_Map::~ECE_Map() = default;

void ECE_Map::initializeObjects()
{
    // initialize map file
    std::fstream mapFile;
    mapFile.open(MAP_PATH);

    // parse the map file
    std::string line;

    for (int i=MAZE_ROWS-1; i>=0; --i)
    {
        mapFile >> line;
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
                    type = Ghost;
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
    return !(initialMap[y][x] == NoPath);
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
