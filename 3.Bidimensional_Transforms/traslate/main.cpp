/**
 * Traslate Figure
 * 
 * Compile in root:
 * g++ 3.Bidimensional_Transforms/traslate/main.cpp -lGL -lGLU -lglut
 * 
 * Compile in current folder:
 * gg++ main.cpp -lGL -lGLU -lglut
 * 
 */

#include <GL/glut.h>
#include "../../utils/colors/colors.h"

#define KEY_LOWER_W 'w'
#define KEY_LOWER_S 's'
#define KEY_LOWER_A 'a'
#define KEY_LOWER_D 'd'

#define KEY_UPPER_W 'W'
#define KEY_UPPER_S 'S'
#define KEY_UPPER_A 'A'
#define KEY_UPPER_D 'D'

float axis_x = 0.0f;
float axis_y = 0.0f;

void draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();

    glTranslatef(axis_x, axis_y, 0.0f);

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
    case KEY_LOWER_W:
    case KEY_UPPER_W:
        axis_y += 0.01f;
        break;

    case KEY_LOWER_S:
    case KEY_UPPER_S:
        axis_y -= 0.01f;
        break;

    case KEY_LOWER_D:
    case KEY_UPPER_D:
        axis_x += 0.01f;
        break;

    case KEY_LOWER_A:
    case KEY_UPPER_A:
        axis_x -= 0.01f;
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
    glutCreateWindow("Traslate");

    glutDisplayFunc(draw);
    glutKeyboardFunc(keyboard);

    init();

    glutMainLoop();

    return 0;
}