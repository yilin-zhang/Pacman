/*
Author: Yilin Zhang
Class: ECE6122
Last Date Modified: 10/24/2020
Description:
OpenGL execution
*/

#include <cmath>
#include "Objects.h"
#include "Maze.h"

// initialize the objects to show
ECE_Maze maze;
ECE_Ghost ghost_1(maze, 7, 10, ECE_Color::GREEN);
ECE_Ghost ghost_2(maze, 8, 10, ECE_Color::PINK);
ECE_Ghost ghost_3(maze, 9, 10, ECE_Color::ORANGE);
ECE_Ghost ghost_4(maze, 8, 10, ECE_Color::RED);
ECE_Pacman pacman(maze, 8, 4);
std::vector<ECE_Coin> coins;
std::vector<ECE_Power> powers;

// initialize the center coordinate and the distance to the center
int angle = 300;
const float centerX = static_cast<float>(MAZE_COLS) / 2.f;
const float centerY = static_cast<float>(MAZE_ROWS) / 2.f;
const float distance = 20;

void init(void)
{
    // OpenGL initialization
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);

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
    for (int x=0; x<=7; ++x)
    {
        for (auto &y : coinPositions[x])
        {
            coins.push_back(ECE_Coin(maze, x, y));
            coins.push_back(ECE_Coin(maze, 16-x, y));
        }

    }
    for (auto &y : coinPositions[8])
        coins.push_back(ECE_Coin(maze, 8, y));

    // powers initialization
    powers.push_back(ECE_Power(maze, 0, 4));
    powers.push_back(ECE_Power(maze, 0, 18));
    powers.push_back(ECE_Power(maze, 16, 4));
    powers.push_back(ECE_Power(maze, 16, 18));

}

void display(void)
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set the camera position
    glLoadIdentity();
    gluLookAt(centerX + distance*std::cos(static_cast<float>(angle)/180.f * M_PI),
              centerY + distance*std::sin(static_cast<float>(angle)/180.f * M_PI),
              20.0,
              centerX, centerY, 0.0,
              0.0, 0.0, 1.0);

    // display all the objects
    ghost_1.display();
    ghost_2.display();
    ghost_3.display();
    ghost_4.display(8, 10.5);
    pacman.display();

    for (auto &coin: coins)
        coin.display();

    for (auto &power: powers)
        power.display();

    maze.display();

    glutSwapBuffers();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 40.0);

    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y)
{
    if (key == 'r' || key == 'R')
    {
        angle = (angle + 5) % 360;
        glutPostRedisplay();
    }
    else if (key == 'w')
    {
        int step = 1;
        pacman.move(UP, step);
        glutPostRedisplay();
    }
    else if (key == 's')
    {
        int step = 1;
        pacman.move(DOWN, step);
        glutPostRedisplay();
    }
    else if (key == 'a')
    {
        int step = 1;
        pacman.move(LEFT, step);
        glutPostRedisplay();
    }
    else if (key == 'd')
    {
        int step = 1;
        pacman.move(RIGHT, step);
        glutPostRedisplay();
    }

}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHT0);

    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    return 0;
}
