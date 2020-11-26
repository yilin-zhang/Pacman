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
        std::cout << "you die!" << std::endl;
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
    if (!isRunning)
        start();

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

void Game::keyboard(int key)
{
    if (!isRunning)
        start();

    switch(key)
    {
        case GLUT_KEY_UP:
            pacman.setDirection(UP);
            break;
        case GLUT_KEY_DOWN:
            pacman.setDirection(DOWN);
            break;
        case GLUT_KEY_LEFT:
            pacman.setDirection(LEFT);
            break;
        case GLUT_KEY_RIGHT:
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

    int coinsCounter = 0;
    int powersCounter = 0;
    for (int x=0; x<MAZE_COLS; ++x)
        for (int y=0; y<MAZE_ROWS; ++y)
        {
            if (map.getObjectType(x, y) == ECE_Map::Coin)
            {
                coins[coinsCounter] = new ECE_Coin(map, static_cast<float>(x), static_cast<float>(y));
                ++coinsCounter;
            }
            else if (map.getObjectType(x, y) == ECE_Map::Power)
            {
                powers[powersCounter] = new ECE_Power(map, static_cast<float>(x), static_cast<float>(y));
                ++powersCounter;
            }
        }
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

void Game::start()
{
    isRunning = true;

    if (!pacman.checkMoving())
        pacman.setMoving(true);

    for (auto & ghost : ghosts)
        if (ghost && !ghost->checkMoving())
            ghost->setMoving(true);
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
                ghostDie(ghost, ghostRebirthTimers[ghostId]);
            else
            {
                pacmanDie();
                return;  // start over
            }
        }
    }

    // multi-thread the path finding
    omp_set_num_threads(4);
    #pragma omp parallel for default(none)
    for (int i=0; i<4; ++i)
    {
        if (ghosts[i])
            pathFinder.updateGhostDirection(pacman, *ghosts[i]);
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
                    ghost = new ECE_Ghost(map, 8.f, 10.f, ghostColors[ghostId]);
                else
                    ghost = new ECE_Ghost(map, 8.f, 10.f, ECE_Color::WHITE);
                ghost->setMoving(true);
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
        pathFinder.setChasing(false);
    }
    else
    {
        // reset the color
        for (int i=0; i<4; ++i)
            if (ghosts[i])
                ghosts[i]->setColor(ghostColors[i]);
        isPoweredUp = false;
        pathFinder.setChasing(true);
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