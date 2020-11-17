/*
Author: Yilin Zhang
Class: ECE6122
Last Date Modified: 10/24/2020
Description:
Class definitions
*/

#include "Objects.h"
#include "Utils.h"


//////////////////////////////////////////////////
/// ECE_Object
//////////////////////////////////////////////////

ECE_Object::ECE_Object() : x(0), y(0), color(ECE_Color::WHITE) {}
ECE_Object::ECE_Object(int x, int y, ECE_Color color)
    : x(x), y(y), color(color) {}
ECE_Object::~ECE_Object(){}

std::array<float, 2> ECE_Object::getCoordinate() const
{
    return positionToCoordinate(x, y);
}

void ECE_Object::setPosition(int x, int y)
{
    if (x < 0)
        this->x = 0;
    else if (x >= MAZE_COLS)
        this->x = MAZE_COLS - 1;
    else
        this->x = x;

    if (y < 0)
        this->y = 0;
    else if (y >= MAZE_ROWS)
        this->y = MAZE_ROWS - 1;
    else
        this->y = y;
}

void ECE_Object::setColor(ECE_Color color)
{
    this->color = color;
}

//////////////////////////////////////////////////
/// ECE_Ghost
//////////////////////////////////////////////////

ECE_Ghost::ECE_Ghost():ECE_Object(){}
ECE_Ghost::ECE_Ghost(int x, int y, ECE_Color color):ECE_Object(x, y, color){}
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

ECE_Pacman::ECE_Pacman():ECE_Object(0, 0, ECE_Color::YELLOW){}
ECE_Pacman::ECE_Pacman(int x, int y):ECE_Object(x, y, ECE_Color::YELLOW){}
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

ECE_Coin::ECE_Coin():ECE_Object(0, 0, ECE_Color::SILVER){}
ECE_Coin::ECE_Coin(int x, int y):ECE_Object(x, y, ECE_Color::SILVER){}
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

ECE_Power::ECE_Power():ECE_Object(0, 0, ECE_Color::GOLDEN){}
ECE_Power::ECE_Power(int x, int y):ECE_Object(x, y, ECE_Color::GOLDEN){}
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

