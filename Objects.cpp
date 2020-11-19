/*
Author: Yilin Zhang
Class: ECE6122
Last Date Modified: 10/24/2020
Description:
Class definitions
*/

#include <cmath>
#include "Objects.h"
#include "Utils.h"

//////////////////////////////////////////////////
/// ECE_Object
//////////////////////////////////////////////////

ECE_Object::ECE_Object(ECE_Map &map, float x, float y, ECE_Color color)
    : map(map), x(x), y(y), color(color) {}
ECE_Object::~ECE_Object()= default;

void ECE_Object::getCoordinate(float &cX, float &cY) const
{
    positionToCoordinate(x, y, cX, cY);
}

void ECE_Object::setPosition(float x, float y)
{
    if (x < 0)
        this->x = 0.f;
    else if (x >= MAZE_COLS)
        this->x = static_cast<float>(MAZE_COLS - 1);
    else
        this->x = x;

    if (y < 0)
        this->y = 0.f;
    else if (y >= MAZE_ROWS)
        this->y = static_cast<float>(MAZE_ROWS - 1);
    else
        this->y = y;
}

void ECE_Object::getPosition(float &x, float &y) const
{
    x = this->x;
    y = this->y;
}

void ECE_Object::setColor(ECE_Color color)
{
    this->color = color;
}

void ECE_Object::move(Direction direction, float distance)
{
    // the current position on grid
    int currentGridX = static_cast<int>(roundf(x));
    int currentGridY = static_cast<int>(roundf(y));

    // the dest position on grid
    int destGridX, destGridY;
    switch(direction)
    {
        case UP:
            destGridY = static_cast<int>(round(y + distance));
            destGridX = currentGridX;
            break;
        case DOWN:
            destGridY = static_cast<int>(round(y - distance));
            destGridX = currentGridX;
            break;
        case LEFT:
            destGridX = static_cast<int>(round(x - distance));
            destGridY = currentGridY;
            break;
        case RIGHT:
        default:
            destGridX = static_cast<int>(round(x + distance));
            destGridY = currentGridY;
            break;
    }

    float destX, destY;
    switch(direction)
    {
        case UP:
            destX = x;
            destY = y + distance;
            break;
        case DOWN:
            destX = x;
            destY = y - distance;
            break;
        case LEFT:
            destY = y;
            destX = x - distance;
            break;
        case RIGHT:
        default:
            destY = y;
            destX = x + distance;
            break;
    }

    bool isGridValid = map.validatePosition(destGridX, destGridY);
    bool isPosValid = map.validatePosition(destX, destY);

    if (isPosValid)
    {
        x = destX;
        y = destY;
        return;
    }

    // position is not valid but the grid is valid
    if (isGridValid)
    {
        x = static_cast<float>(destGridX);
        y = static_cast<float>(destGridY);
        return;
    }
}

//////////////////////////////////////////////////
/// ECE_Ghost
//////////////////////////////////////////////////

ECE_Ghost::ECE_Ghost(ECE_Map &map, float x, float y, ECE_Color color):ECE_Object(map, x, y, color){}
ECE_Ghost::~ECE_Ghost()= default;

void ECE_Ghost::display()
{
    // get coordinate
    float cX, cY;
    getCoordinate(cX, cY);
    display(cX, cY);
}

void ECE_Ghost::display(float cX, float cY)
{
    // get color
    float colorR, colorG, colorB;
    colorToRGBf(color, colorR, colorG, colorB);
    glColor3f(colorR, colorG, colorB);

    auto quadratic = gluNewQuadric();

    glPushMatrix();
    glTranslatef(cX, cY, GRID_SIZE/3.f);
    glutSolidSphere(GRID_SIZE/3.f, 10, 8);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(cX, cY, 0.0);
    gluCylinder(quadratic, GRID_SIZE/3.f, GRID_SIZE/3.f, GRID_SIZE/3.f, 10, 8);
    glPopMatrix();
}

//////////////////////////////////////////////////
/// ECE_Pacman
//////////////////////////////////////////////////

ECE_Pacman::ECE_Pacman(ECE_Map &map, float x, float y):
ECE_Object(map, x, y, ECE_Color::YELLOW),
speed(0.012f * static_cast<float>(FRAME_TIME)), isMoving(false), movingDirection(LEFT){}
ECE_Pacman::~ECE_Pacman()= default;

void ECE_Pacman::display()
{
    // get coordinate
    float cX, cY;
    getCoordinate(cX, cY);

    // get color
    float colorR, colorG, colorB;
    colorToRGBf(color, colorR, colorG, colorB);

    glColor3f(colorR, colorG, colorB);

    auto quadratic = gluNewQuadric();

    glPushMatrix();
    /* Remember reverse order */
    glTranslatef(cX, cY, 0.0);
    glutSolidSphere(0.5, 10, 8);

    glPopMatrix();
}

void ECE_Pacman::setMoving(bool isMoving)
{
    this->isMoving = isMoving;
}

bool ECE_Pacman::checkMoving()
{
    return isMoving;
}

void ECE_Pacman::setDirection(Direction direction)
{
    movingDirection = direction;
}

void ECE_Pacman::updateState()
{
    if (isMoving)
    {
        move(movingDirection, speed);
    }
}

//////////////////////////////////////////////////
/// ECE_Coin
//////////////////////////////////////////////////

ECE_Coin::ECE_Coin(ECE_Map &map, float x, float y):ECE_Object(map, x, y, ECE_Color::SILVER){}
ECE_Coin::~ECE_Coin()= default;

void ECE_Coin::display()
{
    // get coordinate
    float cX, cY;
    getCoordinate(cX, cY);

    // get color
    float colorR, colorG, colorB;
    colorToRGBf(color, colorR, colorG, colorB);

    glColor3f(colorR, colorG, colorB);

    glPushMatrix();
    /* Remember reverse order */
    glTranslatef(cX, cY, 0.0);
    glutSolidSphere(0.1, 10, 8);
    glPopMatrix();
}

//////////////////////////////////////////////////
/// ECE_Power
//////////////////////////////////////////////////

ECE_Power::ECE_Power(ECE_Map &map, float x, float y):ECE_Object(map, x, y, ECE_Color::GOLDEN){}
ECE_Power::~ECE_Power()= default;

void ECE_Power::display()
{
    // get coordinate
    float cX, cY;
    getCoordinate(cX, cY);

    // get color
    float colorR, colorG, colorB;
    colorToRGBf(color, colorR, colorG, colorB);

    glColor3f(colorR, colorG, colorB);
    auto quadratic = gluNewQuadric();

    glPushMatrix();
    glTranslatef(cX, cY, 0.0);
    glTranslatef(0.0, 0.0, -GRID_SIZE/10.f);
    gluDisk(quadratic, 0, GRID_SIZE/3.f, 10, 8);
    glPopMatrix();
}

