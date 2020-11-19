//
// Created by Yilin Zhang on 11/18/20.
//

#include "Game.h"
#include <iostream>

Game::Game():
pacman(map, 8.f, 4.f)
{
    // initialize the ghosts
    ghosts[0] = new ECE_Ghost(map, 7.f, 10.f, ECE_Color::GREEN);
    ghosts[1] = new ECE_Ghost(map, 8.f, 10.f, ECE_Color::PINK);
    ghosts[2] = new ECE_Ghost(map, 9.f, 10.f, ECE_Color::ORANGE);
    ghosts[3] = new ECE_Ghost(map, 8.f, 12.f, ECE_Color::RED);

    // TODO: Ugly code, initialize these using the information in map
    // coins initialization
    std::vector<std::vector<int>> coinPositions(17); // indices of coins in every column
    coinPositions[0] = {0, 1, 2, 5, 6, 14, 15, 16, 17, 19};
    coinPositions[1] = {0, 2, 3, 4, 6, 14, 16, 19};
    coinPositions[2] = {0, 2, 6, 14, 16, 19};
    coinPositions[3] = {0, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};
    coinPositions[4] = {0, 4, 6, 16, 19};
    coinPositions[5] = {0, 2, 3, 4, 6, 14, 15, 16, 19};
    coinPositions[6] = {0, 2, 4, 6, 14, 16, 19};
    coinPositions[7] = {0, 2, 3, 5, 6, 7, 14, 16, 17, 18, 19};
    coinPositions[8] = {0, 16};
    int coinsCounter = 0;
    for (int x=0; x<=7; ++x)
    {
        for (auto &y : coinPositions[x])
        {
            coins[coinsCounter] = new ECE_Coin(map, static_cast<float>(x), static_cast<float>(y));
            ++coinsCounter;
            coins[coinsCounter] = new ECE_Coin(map, static_cast<float>(16-x), static_cast<float>(y));
            ++coinsCounter;
        }
    }
    for (auto &y : coinPositions[8])
    {
        coins[coinsCounter] = new ECE_Coin(map, static_cast<float>(8), static_cast<float>(y));
        ++coinsCounter;
    }

    // initialize power
    powers[0] = new ECE_Power(map, 0.f, 4.f);
    powers[1] = new ECE_Power(map, 0.f, 18.f);
    powers[2] = new ECE_Power(map, 16.f, 4.f);
    powers[3] = new ECE_Power(map, 16.f, 18.f);
}

Game::~Game()
{
    for (auto & ghost : ghosts)
        delete ghost;

    for (auto & coin : coins)
        delete coin;

    for (auto & power : powers)
        delete power;
}

void Game::display()
{
    maze.display();
    pacman.display();

    for (auto & ghost : ghosts)
    {
        if (ghost)
            ghost -> display();
    }

    for (auto & coin : coins)
    {
        if (coin)
            coin -> display();
    }

    for (auto & power : powers)
    {
        if (power)
            power -> display();
    }
}

void Game::keyboard(unsigned char key)
{
    switch(key)
    {
        case 'w':
            pacman.move(UP, 0.2);
            glutPostRedisplay();
            break;
        case 's':
            pacman.move(DOWN, 0.2);
            glutPostRedisplay();
            break;
        case 'a':
            pacman.move(LEFT, 0.2);
            glutPostRedisplay();
            break;
        case 'd':
            pacman.move(RIGHT, 0.2);
            glutPostRedisplay();
            break;
    }
}