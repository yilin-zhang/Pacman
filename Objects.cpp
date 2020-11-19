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

ECE_Object::ECE_Object(ECE_Map &map) : map(map), x(0.f), y(0.f), color(ECE_Color::WHITE) {}
ECE_Object::ECE_Object(ECE_Map &map, float x, float y, ECE_Color color)
    : map(map), x(x), y(y), color(color) {}
ECE_Object::~ECE_Object(){}

std::array<float, 2> ECE_Object::getCoordinate() const
{
    return positionToCoordinate(x, y);
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

ECE_Ghost::ECE_Ghost(ECE_Map &map):ECE_Object(map){}
ECE_Ghost::ECE_Ghost(ECE_Map &map, float x, float y, ECE_Color color):ECE_Object(map, x, y, color){}
ECE_Ghost::~ECE_Ghost(){}

void ECE_Ghost::display()
{
    // get coordinate
    auto coordinate = getCoordinate();
    float cX = coordinate[0];
    float cY = coordinate[1];

    display(cX, cY);
}

void ECE_Ghost::display(float cX, float cY)
{
    // get color
    auto colorRGB = colorToRGBf(color);
    float colorR = colorRGB[0];
    float colorG = colorRGB[1];
    float colorB = colorRGB[2];
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

ECE_Pacman::ECE_Pacman(ECE_Map &map):ECE_Object(map, 0, 0, ECE_Color::YELLOW){}
ECE_Pacman::ECE_Pacman(ECE_Map &map, float x, float y):ECE_Object(map, x, y, ECE_Color::YELLOW){}
ECE_Pacman::~ECE_Pacman(){}

void ECE_Pacman::display()
{
    // get coordinate
    auto coordinate = getCoordinate();
    float cX = coordinate[0];
    float cY = coordinate[1];

    // get color
    auto colorRGB = colorToRGBf(color);
    float colorR = colorRGB[0];
    float colorG = colorRGB[1];
    float colorB = colorRGB[2];
    glColor3f(colorR, colorG, colorB);

    auto quadratic = gluNewQuadric();

    glPushMatrix();
    /* Remember reverse order */
    glTranslatef(cX, cY, 0.0);
    glutSolidSphere(0.5, 10, 8);

    glPopMatrix();
}

//////////////////////////////////////////////////
/// ECE_Coin
//////////////////////////////////////////////////

ECE_Coin::ECE_Coin(ECE_Map &map):ECE_Object(map, 0, 0, ECE_Color::SILVER){}
ECE_Coin::ECE_Coin(ECE_Map &map, float x, float y):ECE_Object(map, x, y, ECE_Color::SILVER){}
ECE_Coin::~ECE_Coin(){}

void ECE_Coin::display()
{
    // get coordinate
    auto coordinate = getCoordinate();
    float cX = coordinate[0];
    float cY = coordinate[1];

    // get color
    auto colorRGB = colorToRGBf(color);
    float colorR = colorRGB[0];
    float colorG = colorRGB[1];
    float colorB = colorRGB[2];

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

ECE_Power::ECE_Power(ECE_Map &map):ECE_Object(map, 0, 0, ECE_Color::GOLDEN){}
ECE_Power::ECE_Power(ECE_Map &map, float x, float y):ECE_Object(map, x, y, ECE_Color::GOLDEN){}
ECE_Power::~ECE_Power(){}

void ECE_Power::display()
{
    // get coordinate
    auto coordinate = getCoordinate();
    float cX = coordinate[0];
    float cY = coordinate[1];

    // get color
    auto colorRGB = colorToRGBf(color);
    float colorR = colorRGB[0];
    float colorG = colorRGB[1];
    float colorB = colorRGB[2];
    glColor3f(colorR, colorG, colorB);
    auto quadratic = gluNewQuadric();

    glPushMatrix();
    glTranslatef(cX, cY, 0.0);
    glTranslatef(0.0, 0.0, -GRID_SIZE/10.f);
    gluDisk(quadratic, 0, GRID_SIZE/3.f, 10, 8);
    glPopMatrix();
}

