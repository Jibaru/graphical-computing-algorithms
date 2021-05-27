/**
 * Bezier Curve with Castelljau Algorithm
 * 
 * Compile in root:
 * g++ 5.Curves/castelljau/main.cpp -lGL -lGLU -lglut
 * 
 * Compile in current folder:
 * g++ main.cpp -lGL -lGLU -lglut
 * 
 * More documentation here:
 * https://pages.mtu.edu/~shene/COURSES/cs3621/NOTES/spline/de-casteljau.html
 * 
 */

#include <vector>
#include <GL/glut.h>

#include "../../utils/colors/colors.h"
#include "../../utils/points/point3d.h"

#define T_START 0.0f
#define T_END 1.0f
#define T_INCREMENT 0.001f

// R3 Points
std::vector<Point3d> points = {
    {-0.89, 0.68, 0.0f},
    {-0.74, -0.57, 0.0f},
    {-0.22, -0.45, 0.0f},
    {0.22, -0.59, 0.0f},
    {0.25, 0.51, 0.1f},
    {0.83, 0.4, 0.6f},
};

int selectedIndex = -1;

Point3d
applyCastelljau(const std::vector<Point3d> &v_points, const float t)
{
    std::vector<Point3d> cpy_points = v_points;

    for (int k = 1; k < points.size(); k++)
    {
        for (int i = 0; i < points.size() - 1; i++)
        {
            cpy_points[i] = (1 - t) * cpy_points[i] + t * cpy_points[i + 1];
        }
    }

    return cpy_points[0];
}

void drawSelectedPoint(const Point3d &point)
{
    glColor3f(GLUT_RED_COLOR);
    glPointSize(10.0f);
    glBegin(GL_POINTS);
    glVertex3f(point.x, point.y, point.z);
    glEnd();
    glPointSize(2.0f);
}

void draw()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    glPushMatrix();

    // R3 Polylines
    glBegin(GL_LINE_STRIP);
    glColor3f(GLUT_GREEN_COLOR);
    for (int i = 0; i < points.size(); i++)
    {
        glVertex3f(points[i].x, points[i].y, points[i].z);
    }
    glEnd();

    if (selectedIndex != -1)
    {
        drawSelectedPoint(points[selectedIndex]);
    }

    // Bezier Curve
    glBegin(GL_POINTS);
    glColor3f(GLUT_YELLOW_COLOR);
    for (float t = T_START; t <= T_END; t += T_INCREMENT)
    {
        Point3d p = applyCastelljau(points, t);
        glVertex3f(p.x, p.y, p.z);
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
            if (convX >= points[i].x - 0.02 && convX <= points[i].x + 0.02 &&
                convY >= points[i].y - 0.02 && convY <= points[i].y + 0.02)
            {
                selectedIndex = i;
            }
        }
    }
    else if (button == GLUT_LEFT_BUTTON && selectedIndex != -1)
    {
        points[selectedIndex].x = convX;
        points[selectedIndex].y = convY;
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
    glutCreateWindow("Bezier Curve with Castelljau");

    glutDisplayFunc(draw);
    glutMouseFunc(mouse);

    init();

    glutMainLoop();

    return 0;
}