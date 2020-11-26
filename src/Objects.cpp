//
// Created by Yilin Zhang on 11/24/20.
//

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


//////////////////////////////////////////////////
/// ECE_Character
//////////////////////////////////////////////////

ECE_Character::ECE_Character(ECE_Map &map, float x, float y, ECE_Color color, float speed):
ECE_Object(map, x, y, color),
speed(speed), isMoving(false), movingDirection(UP){} // this initial direction is important for AI to work properly
ECE_Character::~ECE_Character()= default;

void ECE_Character::move(Direction direction, float distance)
{
    // the current position on grid
    int currentGridX = static_cast<int>(roundf(x));
    int currentGridY = static_cast<int>(roundf(y));

    // the dest position on grid
    int destGridX, destGridY;
    float destX, destY;
    switch(direction)
    {
        case UP:
            destGridY = static_cast<int>(round(y + distance));
            destGridX = currentGridX;
            destX = x;
            destY = y + distance;
            break;
        case DOWN:
            destGridY = static_cast<int>(round(y - distance));
            destGridX = currentGridX;
            destX = x;
            destY = y - distance;
            break;
        case LEFT:
            destGridX = static_cast<int>(round(x - distance));
            destGridY = currentGridY;
            destY = y;
            destX = x - distance;
            break;
        case RIGHT:
        default:
            destGridX = static_cast<int>(round(x + distance));
            destGridY = currentGridY;
            destY = y;
            destX = x + distance;
            break;
    }

    // handle the special case
    if (destGridY == 10)
    {
        if ((destX < 0.f && destX >= -1.f) ||
            (destX > static_cast<float>(MAZE_COLS - 1) && destX <= static_cast<float>(MAZE_COLS)))
        {
            x = destX;
            y = destY;
            return;
        }
        if (destX < -1.f)
        {
            x = static_cast<float>(MAZE_COLS) - distance;
            y = destY;
            return;
        }

        if (destX > static_cast<float>(MAZE_COLS))
        {
            x = -1.f + distance;
            y = destY;
            return;
        }
    }

    // make sure the ghosts can move out from home
    bool isGridValid = map.validatePositionWhenGateOpen(destGridX, destGridY);
    bool isPosValid = map.validatePositionWhenGateOpen(destX, destY);

    if (isPosValid)
    {
        x = destX;
        y = destY;
        return;
    }

    // position is not valid but the grid is valid
    // it means the character is stuck
    if (isGridValid)
    {
        x = static_cast<float>(destGridX);
        y = static_cast<float>(destGridY);
        return;
    }
}

void ECE_Character::setMoving(bool isMoving)
{
    this->isMoving = isMoving;
}

bool ECE_Character::checkMoving() const
{
    return isMoving;
}

void ECE_Character::setDirection(Direction direction)
{
    movingDirection = direction;
}

Direction ECE_Character::getDirection() const
{
    return movingDirection;
}

void ECE_Character::updatePosition()
{
    if (isMoving)
        move(movingDirection, speed);
}

//////////////////////////////////////////////////
/// ECE_Ghost
//////////////////////////////////////////////////

ECE_Ghost::ECE_Ghost(ECE_Map &map, float x, float y, ECE_Color color):
ECE_Character(map, x, y, color, GHOST_SPEED) {}
ECE_Ghost::~ECE_Ghost()= default;

void ECE_Ghost::display()
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
ECE_Character(map, x, y, ECE_Color::YELLOW, PACMAN_SPEED) {}
ECE_Pacman::~ECE_Pacman()= default;

void ECE_Pacman::setDirection(Direction direction)
{
    auto gridX = static_cast<int>(round(x));
    auto gridY = static_cast<int>(round(y));
    bool isValid = false;
    switch (direction)
    {
        case UP:
            isValid = map.validatePosition(gridX, gridY + 1);
            break;
        case DOWN:
            isValid = map.validatePosition(gridX, gridY - 1);
            break;
        case LEFT:
            isValid = map.validatePosition(gridX - 1, gridY);
            break;
        case RIGHT:
            isValid = map.validatePosition(gridX + 1, gridY);
            break;
    }

    if (isValid)
        movingDirection = direction;
}

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

