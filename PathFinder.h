//
// Created by Yilin Zhang on 11/22/20.
//

#pragma once
#include "Objects.h"

class PathFinder
{
public:
    explicit PathFinder(const ECE_Map &map);
    ~PathFinder();
    void updateGhostDirection(const ECE_Pacman &pacman, ECE_Ghost &ghost);
    void setChasing(bool isChasing);

private:
    const ECE_Map &map;
    bool isChasing;  // true indicates chasing mode, false indicates frightened mode
};


