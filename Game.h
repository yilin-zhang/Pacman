//
// Created by Yilin Zhang on 11/18/20.
//

#pragma once
#include "Map.h"
#include "Maze.h"
#include "Objects.h"
#include <array>

class Game
{
public:
    Game();
    ~Game();

    void display();

    void keyboard(unsigned char key);

private:
    void check();
    void setPowerUp(bool isPowerUp);

    ECE_Map map;
    ECE_Maze maze;
    ECE_Pacman pacman;
    std::array<ECE_Ghost*, 4> ghosts;
    std::array<ECE_Coin*, 152> coins;
    std::array<ECE_Power*, 4> powers;

    bool isPoweredUp;
};

