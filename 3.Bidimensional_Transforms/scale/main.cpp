/**
 * Scale Figure
 * 
 * Compile in root:
 * g++ 3.Bidimensional_Transforms/scale/main.cpp -lGL -lGLU -lglut
 * 
 * Compile in current folder:
 * gg++ main.cpp -lGL -lGLU -lglut
 * 
 */

#include <GL/glut.h>
#include "../../utils/colors/colors.h"

#define KEY_PLUS '+'
#define KEY_MINUS '-'

float scale_x = 1.0f;
float scale_y = 1.0f;

void draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();

    glScaled(scale_x, scale_y, 1.0f);

    glBegin(GL_QUADS);
    glColor3f(GLUT_YELLOW_COLOR);
    glVertex2f(-0.1f, -0.1f);
    glVertex2f(0.1f, -0.1f);
    glVertex2f(0.1f, 0.1f);
    glVertex2f(-0.1f, 0.1f);
    glEnd();

    glPopMatrix();

    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case KEY_PLUS:
        scale_x += 0.1f;
        scale_y += 0.1f;
        break;

    case KEY_MINUS:
        scale_x -= 0.1f;
        scale_y -= 0.1f;
        break;
    }

    glutPostRedisplay();
}

void init()
{
    glClearColor(GLUT_BLUE_COLOR, 1.0f);
    glPointSize(5.0f);
    glOrtho(800, 0, 600, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char *args[])
{
    glutInit(&argc, args);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

    glutInitWindowSize(800, 600);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Scale");

    glutDisplayFunc(draw);
    glutKeyboardFunc(keyboard);

    init();

    glutMainLoop();

    return 0;
}