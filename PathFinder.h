//
// Created by Yilin Zhang on 11/22/20.
//

#pragma once
#include "Objects.h"

class PathFinder
{
public:
    PathFinder(const ECE_Map &map);
    ~PathFinder();
    void updateGhostDirection(const ECE_Pacman &pacman, ECE_Ghost &ghost);

private:
    const ECE_Map &map;
};


