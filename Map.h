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

    /** Validate the given position and assume the gate is open
     * @param x
     * @param y
     * @return
     */
    bool validatePositionWhenGateOpen(int x, int y) const;

    /** Validate the given position and assume the gate is open
     * @param x
     * @param y
     * @return
     */
    bool validatePositionWhenGateOpen(float x, float y) const;

    /** Get the object type at the position (x, y)
     * @param x
     * @param y
     * @return
     */
    ObjectType getObjectType(int x, int y) const;

private:
    void initializeObjects();
    std::array<std::array<ObjectType, MAZE_COLS>, MAZE_ROWS> initialMap; // x and y are reversed
};


