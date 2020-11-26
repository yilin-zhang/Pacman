//
// Created by Yilin Zhang on 11/18/20.
//

#pragma once
#include "Map.h"
#include "Maze.h"
#include "Objects.h"
#include "Utils.h"
#include "PathFinder.h"
#include <array>

class Game
{
public:
    Game();
    ~Game();

    /** Updates the game state for a frame */
    void updateState();

    /** Displays all the objects on the screen */
    void display();

    /** Receives the key and triggers the change of the game state
     * @param key any key in 'a', 's', 'd' and 'w'
     */
    void keyboard(unsigned char key);

    /** Receives the key and triggers the change of the game state
     * @param key any arrow key
     */
    void keyboard(int key);

    /** Resets the game */
    void reset();

private:
    /** Initializes all the visual objects in the game */
    void initializeObjects();

    /** Releases the memory for the objects */
    void releaseResources();

    /** Starts the game (sets the pacman and the ghosts to moving state) */
    void start();

    /** Checks the current state and do some updates */
    void check();
    void checkGhosts();
    void checkCoins();
    void checkPowers();
    void checkClear();
    void checkGhostRespawn();

    /** Turns on or off the power-up state
     * @param isPowerUp
     */
    void setPowerUp(bool isPowerUp);

    /** Sets the pacman die and change the status */
    void pacmanDie();

    /** Sets the ghost Die
     * @param ghost
     */
    static void ghostDie(ECE_Ghost* &ghost, Timer &rebirthTimer);

    /** Resets the game because of the pacman death */
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
    // path finder
    PathFinder pathFinder;
    // handling power-up
    bool isPoweredUp;
    Timer powerUpTimer;
    // handling the rebirth of ghosts
    std::array<Timer, 4> ghostRebirthTimers;
    Timer lastGhostRebirthTimer;
    // game status
    bool isRunning;
    bool isWin;
    bool isDead;
    bool isLost;
    int numDeaths;
};

