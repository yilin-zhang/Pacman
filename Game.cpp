//
// Created by Yilin Zhang on 11/18/20.
//

#include "Game.h"
#include <iostream>
#include <cmath>

Game::Game():
pacman(map, 8.f, 4.f),
ghosts(), coins(), powers(), // empty arrays
pathFinder(map),
isRunning(false), isPoweredUp(false), isWin(false), isDead(false), isLost(false), numDeaths(0)
{
    initializeObjects();
}

Game::~Game()
{
    releaseResources();
}

void Game::updateState()
{
    if (!isRunning)
        return;

    // update the states
    pacman.updatePosition();
    for (auto & ghost : ghosts)
        if (ghost)
            ghost->updatePosition();

    check();

    if (isWin)
    {
        reset();
        std::cout << "you win!" << std::endl;
        return;
    }

    if (isLost)
    {
        reset();
        std::cout << "you lose!" << std::endl;
        return;
    }

    if (isDead)
    {
        resetForDeath();
        std::cout << "you dead!" << std::endl;
        return;
    }
}

void Game::display()
{
    maze.display();
    pacman.display();

    for (auto & ghost : ghosts)
        if (ghost)
            ghost -> display();

    for (auto & coin : coins)
        if (coin)
            coin -> display();

    for (auto & power : powers)
        if (power)
            power -> display();
}

void Game::keyboard(unsigned char key)
{
    if (!(key == 'w' || key == 's' || key == 'a' || key == 'd'))
        return;

    isRunning = true;

    if (!pacman.checkMoving())
        pacman.setMoving(true);

    for (auto & ghost : ghosts)
        if (ghost && !ghost->checkMoving())
            ghost->setMoving(true);

    switch(key)
    {
        case 'w':
            pacman.setDirection(UP);
            break;
        case 's':
            pacman.setDirection(DOWN);
            break;
        case 'a':
            pacman.setDirection(LEFT);
            break;
        case 'd':
            pacman.setDirection(RIGHT);
            break;
    }
}

void Game::reset()
{
    releaseResources();
    initializeObjects();
    pacman.setMoving(false);
    isRunning = false;
    isPoweredUp = false;
    isWin = false;
    isDead = false;
    isLost = false;
    numDeaths = 0;
}

void Game::initializeObjects()
{
    pacman.setPosition(8.f, 4.f);

    // initialize the ghosts
    ghosts[0] = new ECE_Ghost(map, 7.f, 10.f, ghostColors[0]);
    ghosts[1] = new ECE_Ghost(map, 8.f, 10.f, ghostColors[1]);
    ghosts[2] = new ECE_Ghost(map, 9.f, 10.f, ghostColors[2]);
    ghosts[3] = new ECE_Ghost(map, 8.f, 12.f, ghostColors[3]);

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
    coinPositions[7] = {0, 1, 2, 4, 5, 6, 14, 16, 17, 18, 19};
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

void Game::releaseResources()
{
    for (auto & ghost : ghosts)
    {
        delete ghost;
        ghost = nullptr;
    }

    for (auto & coin : coins)
    {
        delete coin;
        coin = nullptr;
    }

    for (auto & power : powers)
    {
        delete power;
        power = nullptr;
    }
}

void Game::check()
{
    // 1. isFinished if the ghosts need to change their directions
    checkGhosts();

    // 2. isFinished if the pacman is close to a coin or a power
    // remove the coin if they are close
    checkCoins();
    checkPowers();

    // 3. isFinished if the board is clear
    checkClear();

    // 4. check if a ghost should respawn
    checkGhostRespawn();

    // isFinished if powered up
    if (isPoweredUp)
    {
        powerUpTimer.update();
        // if the time is up, turn the power-up off
        if (powerUpTimer.isFinished())
            setPowerUp(false);
    }
}

void Game::checkGhosts()
{
    float ghostX, ghostY, pacmanX, pacmanY;
    int ghostId = -1;

    pacman.getPosition(pacmanX, pacmanY);

    for (auto & ghost : ghosts)
    {
        ++ghostId;

        if (!ghost)
            continue;

        ghost->getPosition(ghostX, ghostY);

        // isFinished if the pacman and the ghost is very close
        if (sqrt(pow(ghostX - pacmanX, 2) + pow(ghostY - pacmanY, 2))
            <= DISTANCE_THRESHOLD)
        {
            if (isPoweredUp)
            {
                ghostDie(ghost, ghostRebirthTimers[ghostId]);
                continue;
            }
            else
            {
                // the pacman die
                pacmanDie();
                return;
            }
        }

        // TODO: multithread-this part
        pathFinder.updateGhostDirection(pacman, *ghost);
    }
}

void Game::checkCoins()
{
    float pacmanX, pacmanY;
    float x, y;

    pacman.getPosition(pacmanX, pacmanY);

    for (auto &coin : coins)
    {
        if (coin)
        {
            coin->getPosition(x, y);

            if (sqrt(pow(pacmanX - x, 2) + pow(pacmanY - y, 2)) < DISTANCE_THRESHOLD)
            {
                delete coin;
                coin = nullptr;
            }
        }
    }
}

void Game::checkPowers()
{
    float pacmanX, pacmanY;
    float x, y;

    pacman.getPosition(pacmanX, pacmanY);

    for (auto &power : powers)
    {
        if (power)
        {
            power->getPosition(x, y);

            if (sqrt(pow(pacmanX - x, 2) +
                     pow(pacmanY - y, 2)) < DISTANCE_THRESHOLD)
            {
                // remove the powerup
                delete power;
                power = nullptr;

                setPowerUp(true);
            }
        }
    }
}

void Game::checkClear()
{
    for (auto &coin : coins)
        if (coin)
            return;

    for (auto &power : powers)
        if (power)
            return;

    isWin = true;
}

void Game::checkGhostRespawn()
{
    // update the timers
    for (auto & timer : ghostRebirthTimers)
        timer.update();

    lastGhostRebirthTimer.update();

    int ghostId = 0;
    for (auto & ghost : ghosts)
    {
        // if there's no ghost respawning within the minimum duration
        if (lastGhostRebirthTimer.isFinished())
        {
            // check if the corresponding timer is finished and the ghost does not exist
            if (!ghost && ghostRebirthTimers[ghostId].isFinished())
            {
                if (!isPoweredUp)
                    ghost = new ECE_Ghost(map, 8.f, 12.f, ghostColors[ghostId]);
                else
                    ghost = new ECE_Ghost(map, 8.f, 12.f, ECE_Color::WHITE);

                lastGhostRebirthTimer.start(MIN_RESPAWN_DURATION); // start the timer
            }
        }
        ++ghostId;
    }
}

void Game::setPowerUp(bool isPowerUp)
{
    if (isPowerUp)
    {
        powerUpTimer.start(POWERUP_DURATION);
        for (auto & ghost : ghosts)
            if (ghost)
                ghost->setColor(ECE_Color::WHITE);

        isPoweredUp = true;
    }
    else
    {
        // reset the color
        for (int i=0; i<4; ++i)
            if (ghosts[i])
                ghosts[i]->setColor(ghostColors[i]);
        isPoweredUp = false;
    }
}

void Game::pacmanDie()
{
    ++numDeaths;
    isDead = true;
    if (numDeaths == 3)
        isLost = true;
}

void Game::ghostDie(ECE_Ghost* &ghost, Timer &rebirthTimer)
{
    delete ghost;
    ghost = nullptr;
    rebirthTimer.start(GHOST_RESPAWN_TIME);
}

void Game::resetForDeath()
{
    releaseResources();
    initializeObjects();
    pacman.setMoving(false);
    isRunning = false;
    isPoweredUp = false;
    isWin = false;
    isDead = false;
}