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

    enum ObjectType {Coin, Power, Pacman, Path, NoPath, Gate};

    /** Validates the given position
     * @param x
     * @param y
     * @return true if the position is valid
     */
    bool validatePosition(int x, int y) const;

    /** Validates the given position
     * @param x
     * @param y
     * @return true if the position is valid
     */
    bool validatePosition(float x, float y) const;

    /** Validates the given position and assume the gate is open
     * @param x
     * @param y
     * @return true if the position is valid
     */
    bool validatePositionWhenGateOpen(int x, int y) const;

    /** Validates the given position and assume the gate is open
     * @param x
     * @param y
     * @return true if the position is valid
     */
    bool validatePositionWhenGateOpen(float x, float y) const;

    /** Returns the object type at the position (x, y)
     * @param x
     * @param y
     * @return true if the position is valid
     */
    ObjectType getObjectType(int x, int y) const;

private:
    /** Initialize the `initialMap` that contains the positions of all the objects at the beginning */
    void initializeObjects();
    std::array<std::array<ObjectType, MAZE_COLS>, MAZE_ROWS> initialMap; // x and y are reversed
};


