/**
 * Hermite Curve
 * 
 * Compile in root:
 * g++ 5.Curves/hermite/main.cpp -lGL -lGLU -lglut
 * 
 * Compile in current folder:
 * g++ main.cpp -lGL -lGLU -lglut
 * 
 */

#include <vector>
#include <math.h>
#include <GL/glut.h>

#include "../../utils/colors/colors.h"
#include "../../utils/points/point2d.h"
#include "../../utils/vector/mathvec2d.h"

#define T_END 1.0f
#define T_INCREMENT 0.001f

// Interpolation points
MathVec2d p({-0.4, -0.19}, {0.105, -0.63});
MathVec2d q({0.325, 0.44}, {0.33, -0.22});

std::vector<Point2d *> points = {
    &p.start,
    &p.end,
    &q.start,
    &q.end};

int parts = 40;
int selectedIndex = -1;

void drawSelectedPoint(const Point2d &point)
{
    glColor3f(GLUT_RED_COLOR);
    glPointSize(10.0f);
    glBegin(GL_POINTS);
    glVertex2f(point.x, point.y);
    glEnd();
    glPointSize(2.0f);
}

void draw()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    glPushMatrix();

    // Draw vectors
    glBegin(GL_LINES);
    glColor3f(GLUT_GREEN_COLOR);
    glVertex2f(p.start.x, p.start.y);
    glVertex2f(p.end.x, p.end.y);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(GLUT_GREEN_COLOR);
    glVertex2f(q.start.x, q.start.y);
    glVertex2f(q.end.x, q.end.y);
    glEnd();

    if (selectedIndex != -1)
    {
        drawSelectedPoint(*points[selectedIndex]);
    }

    // Hermite Curve
    glBegin(GL_POINTS);
    glColor3f(GLUT_YELLOW_COLOR);
    Point2d a;
    float t2 = T_END / (float)parts;
    for (float t = t2; t <= T_END; t += T_INCREMENT)
    {
        a = ((2 * pow(t, 3)) - (3 * pow(t, 2)) + 1) * p.start +
            ((-2 * pow(t, 3)) + (3 * pow(t, 2))) * q.start +
            (pow(t, 3) - 2 * pow(t, 2) + t) * p.end +
            (pow(t, 3) - pow(t, 2)) * q.end;
        glVertex2f(a.x, a.y);
    }
    glVertex3f(1.0f, 0.0f, 0.0f);
    glEnd();

    glPopMatrix();
    glutSwapBuffers();
}

void mouse(int button, int state, int x, int y)
{
    float transformX = -400.0f + (float)x;
    float transformY = 300.0f - (float)y;

    float convX = transformX / 400.0f;
    float convY = transformY / 300.0f;

    if (button == GLUT_RIGHT_BUTTON)
    {
        selectedIndex = -1;
        for (int i = 0; selectedIndex == -1 && i < points.size(); i++)
        {
            if (convX >= points[i]->x - 0.02 && convX <= points[i]->x + 0.02 &&
                convY >= points[i]->y - 0.02 && convY <= points[i]->y + 0.02)
            {
                selectedIndex = i;
            }
        }
    }
    else if (button == GLUT_LEFT_BUTTON && selectedIndex != -1)
    {
        points[selectedIndex]->x = convX;
        points[selectedIndex]->y = convY;
    }

    glutPostRedisplay();
}

void init()
{
    glClearColor(GLUT_BLUE_COLOR, 1.0f);
    glPointSize(2.0f);
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
    glutCreateWindow("Hermite Curve");

    glutDisplayFunc(draw);
    glutMouseFunc(mouse);

    init();

    glutMainLoop();

    return 0;
}