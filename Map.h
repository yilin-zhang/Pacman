//
// Created by Yilin Zhang on 11/18/20.
//

#pragma once
#include <array>
#include "Config.h"

class ECE_Map
{
public:
    ECE_Map();
    ~ECE_Map();

    enum ObjectType {Coin, Power, Ghost, Pacman, Path, NoPath};

    /** Validate the given position
     * @param x
     * @param y
     * @return
     */
    bool validatePosition(int x, int y) const;

    /** Validate the given position
     * @param x
     * @param y
     * @return
     */
    bool validatePosition(float x, float y) const;

private:
    void initializeObjects();
    std::array<std::array<ObjectType, MAZE_COLS>, MAZE_ROWS> initialMap;
};


