/*
Author: Yilin Zhang
Class: ECE6122
Last Date Modified: 10/24/2020
Description:
OpenGL execution
*/

#include <cmath>
#include "Game.h"

// initialize the objects to show
Game game;

int angle = 300;
const float centerX = static_cast<float>(MAZE_COLS) / 2.f;
const float centerY = static_cast<float>(MAZE_ROWS) / 2.f;
const float distance = 20;

void init(void)
{
    // OpenGL initialization
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);
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

    game.display();

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
    }

    game.keyboard(key);
}

void frameUpdateTimer(int value)
{
    game.updateState();
    display();
    glutTimerFunc(FRAME_TIME, frameUpdateTimer, 0);
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
    glutTimerFunc(FRAME_TIME, frameUpdateTimer, 0);

    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHT0);

    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    return 0;
}
