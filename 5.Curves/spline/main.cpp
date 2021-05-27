/**
 * Spline Curve
 * 
 * Compile in root:
 * g++ 5.Curves/spline/main.cpp -lGL -lGLU -lglut
 * 
 * Compile in current folder:
 * g++ main.cpp -lGL -lGLU -lglut
 * 
 * More information at:
 * https://en.wikipedia.org/wiki/B-spline
 * https://pages.mtu.edu/~shene/COURSES/cs3621/NOTES/spline/B-spline/bspline-property.html
 * https://pages.mtu.edu/~shene/COURSES/cs3621/NOTES/spline/B-spline/bspline-curve-open.html
 * 
 */

#include <vector>
#include <GL/glut.h>

#include "../../utils/colors/colors.h"
#include "../../utils/points/point2d.h"

#define T_START 0.0f
#define T_END 1.0f
#define T_INCREMENT 0.001f

// R2 Points
std::vector<Point2d> points = {
    {-0.89, 0.68},
    {-0.74, -0.57},
    {-0.22, -0.45},
    {0.22, -0.59},
    {0.25, 0.51},
    {0.83, 0.4},
};

int selectedIndex = -1;

// Change to apply different degrees
int splineDegrees = 3;

float blend(
    const std::vector<float> &uVec,
    const float &t,
    const int &i,
    const int &d)
{
    // B-Spline condition
    if (d == 1)
    {
        if (uVec[i] <= t && t < uVec[i + 1])
            return 1;
        return 0;
    }

    // B-Spline recursive definition
    float b = ((t - uVec[i]) / (uVec[i + d - 1] - uVec[i]) *
               blend(uVec, t, i, d - 1)) +
              ((uVec[i + d] - t) / (uVec[i + d] - uVec[i + 1]) *
               blend(uVec, t, i + 1, d - 1));

    return b;
}

Point2d applyBSpline(
    const std::vector<Point2d> &v_points,
    const std::vector<float> &uVec,
    const int &degrees,
    const float &t)
{
    Point2d p;
    float basis;
    for (int i = 0; i < points.size(); i++)
    {
        basis = blend(uVec, t, i, degrees);
        p.x += basis * points[i].x;
        p.y += basis * points[i].y;
    }

    return p;
}

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

    // R3 Polylines
    glBegin(GL_LINE_STRIP);
    glColor3f(GLUT_GREEN_COLOR);
    for (int i = 0; i < points.size(); i++)
    {
        glVertex3f(points[i].x, points[i].y, 0.0f);
    }
    glEnd();

    if (selectedIndex != -1)
    {
        drawSelectedPoint(points[selectedIndex]);
    }

    // B-Spline Curve
    glBegin(GL_POINTS);
    glColor3f(GLUT_YELLOW_COLOR);
    Point2d c;

    // Fill Knot Vector
    // uVec size = pointsNumber + degree + 1
    std::vector<float> aux, uVec;
    int n = points.size();
    for (int i = 1; i <= n + splineDegrees + 1; i++)
    {
        uVec.push_back(((float)i) / (n + splineDegrees - 1));
    }

    for (float t = T_START; t <= T_END; t += T_INCREMENT)
    {
        c = applyBSpline(points, uVec, splineDegrees, t);
        glVertex3f(c.x, c.y, 0.0f);
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
    glutCreateWindow("B-Spline Curve");

    glutDisplayFunc(draw);
    glutMouseFunc(mouse);

    init();

    glutMainLoop();

    return 0;
}