/**
 * Scale Figure 3D
 * 
 * Compile in root:
 * g++ 4.Tridimensional_Transforms/scale/main.cpp -lGL -lGLU -lglut
 * 
 * Compile in current folder:
 * g++ main.cpp -lGL -lGLU -lglut
 * 
 */

#include <GL/glut.h>
#include "../../utils/colors/colors.h"

#define KEY_LOWER_A 'a'
#define KEY_LOWER_D 'd'
#define KEY_LOWER_W 'w'
#define KEY_LOWER_S 's'
#define KEY_LOWER_Z 'z'
#define KEY_LOWER_C 'c'

#define KEY_UPPER_A 'A'
#define KEY_UPPER_D 'D'
#define KEY_UPPER_W 'W'
#define KEY_UPPER_S 'S'
#define KEY_UPPER_Z 'Z'
#define KEY_UPPER_C 'C'

float angle_x = 12.5f;
float angle_y = 50.0f;
float angle_z = 15.5f;

float scale_x = 1.0f;
float scale_y = 1.0f;
float scale_z = 1.0f;

void draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glPushMatrix();

    glRotated(angle_x, 1.0f, 0.0f, 0.0f);
    glRotated(angle_y, 0.0f, 1.0f, 0.0f);
    glRotated(angle_z, 0.0f, 0.0f, 1.0f);

    glScaled(scale_x, scale_y, scale_y);

    glBegin(GL_QUADS);
    glColor3f(GLUT_GREEN_COLOR);
    glVertex3f(0.1f, 0.1f, -0.1f);
    glVertex3f(-0.1f, 0.1f, -0.1f);
    glVertex3f(-0.1f, 0.1f, 0.1f);
    glVertex3f(0.1f, 0.1f, 0.1f);

    glColor3f(GLUT_CYAN_COLOR);
    glVertex3f(0.1f, -0.1f, 0.1f);
    glVertex3f(-0.1f, -0.1f, 0.1f);
    glVertex3f(-0.1f, -0.1f, -0.1f);
    glVertex3f(0.1f, -0.1f, -0.1f);

    glColor3f(GLUT_RED_COLOR);
    glVertex3f(0.1f, 0.1f, 0.1f);
    glVertex3f(-0.1f, 0.1f, 0.1f);
    glVertex3f(-0.1f, -0.1f, 0.1f);
    glVertex3f(0.1f, -0.1f, 0.1f);

    glColor3f(GLUT_YELLOW_COLOR);
    glVertex3f(0.1f, -0.1f, -0.1f);
    glVertex3f(-0.1f, -0.1f, -0.1f);
    glVertex3f(-0.1f, 0.1f, -0.1f);
    glVertex3f(0.1f, 0.1f, -0.1f);

    glColor3f(GLUT_WHITE_COLOR);
    glVertex3f(-0.1f, 0.1f, 0.1f);
    glVertex3f(-0.1f, 0.1f, -0.1f);
    glVertex3f(-0.1f, -0.1f, -0.1f);
    glVertex3f(-0.1f, -0.1f, 0.1f);

    glColor3f(GLUT_MAGENTA_COLOR);
    glVertex3f(0.1f, 0.1f, -0.1f);
    glVertex3f(0.1f, 0.1f, 0.1f);
    glVertex3f(0.1f, -0.1f, 0.1f);
    glVertex3f(0.1f, -0.1f, -0.1f);

    glEnd();

    glPopMatrix();

    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case KEY_LOWER_A:
    case KEY_UPPER_A:
        scale_x += 0.1f;
        break;

    case KEY_LOWER_D:
    case KEY_UPPER_D:
        scale_x -= 0.1f;
        break;

    case KEY_LOWER_S:
    case KEY_UPPER_S:
        scale_y += 0.1f;
        break;

    case KEY_LOWER_W:
    case KEY_UPPER_W:
        scale_y -= 0.1f;
        break;

    case KEY_LOWER_Z:
    case KEY_UPPER_Z:
        scale_z += 0.1f;
        break;

    case KEY_LOWER_C:
    case KEY_UPPER_C:
        scale_z -= 0.1f;
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
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutInitWindowSize(800, 600);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Scale 3D");

    glutDisplayFunc(draw);
    glutKeyboardFunc(keyboard);

    init();

    glutMainLoop();

    return 0;
}