#include <iostream>
#include <vector>
#include <functional>
#include <GL/glut.h>
#include "Painter.h"

std::vector<std::function<void()>> DisplayCallbacks;

void Painter::Display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);

    for (int i = 0; i < DisplayCallbacks.size(); i++)
    {
        DisplayCallbacks[i]();
    }

    glFlush();
}

void Painter::Window(const char *title, const float &width, const float &height, int &argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow(title);

    glutDisplayFunc(Painter::Display);

    glClearColor(1.0, 1.0, 1.0, 1.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(0.0, 499.0, 0.0, 499.0);
}

void Painter::StartLoop()
{
    glutMainLoop();
}

void Painter::Point(const float x, const float y, const float size = 5.0)
{
    DisplayCallbacks.push_back([x, y, size] {
        glPointSize(size);
        glColor3f(1.0f, 0.0f, 0.0f);
        glBegin(GL_POINTS);
        glVertex2f(x, y);
        glEnd();
    });
}