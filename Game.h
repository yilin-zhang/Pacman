//
// Created by Yilin Zhang on 11/18/20.
//

#pragma once
#include "Map.h"
#include "Maze.h"
#include "Objects.h"
#include "Utils.h"
#include <array>

class Game
{
public:
    Game();
    ~Game();

    void updateState();

    void display();

    void keyboard(unsigned char key);

    void reset();

private:
    void initializeObjects();
    void releaseResources();

    /** Check the current state and do some updates
     */
    void check();
    void checkGhosts();
    void checkCoins();
    void checkPowers();
    void checkClear();

    /** Turn on or off the power-up state
     * @param isPowerUp
     */
    void setPowerUp(bool isPowerUp);

    /** Set the pacman die and change the status
     */
    void pacmanDie();

    static void ghostDie(ECE_Ghost* &ghost);

    void resetForDeath();

    /// objects in the game
    ECE_Map map;
    ECE_Maze maze;
    ECE_Pacman pacman;
    std::array<ECE_Ghost*, 4> ghosts;
    std::array<ECE_Coin*, 152> coins;
    std::array<ECE_Power*, 4> powers;
    const std::array<ECE_Color, 4> ghostColors = {ECE_Color::GREEN, ECE_Color::PINK, ECE_Color::ORANGE, ECE_Color::RED};

    /// other members
    bool isPoweredUp;
    Timer powerUpTimer;
    bool isWin;
    bool isDead;
    bool isLost;
    int numDeaths;
};

