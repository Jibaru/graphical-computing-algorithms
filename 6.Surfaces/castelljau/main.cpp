/**
 * Bezier Surfaces with Castelljau Algorithm
 * 
 * Compile in root:
 * g++ 5.Curves/castelljau/main.cpp -lGL -lGLU -lglut
 * 
 * Compile in current folder:
 * g++ main.cpp -lGL -lGLU -lglut
 * 
 */

#include <iostream>
#include <vector>
#include <GL/glut.h>

#include "../../utils/colors/colors.h"
#include "../../utils/keys/keys.h"
#include "../../utils/points/point3d.h"

#define T_START 0.0f
#define T_END 1.0f
#define T_INCREMENT 0.001f

float angle_x = 0.0f;
float angle_y = 0.0f;
float angle_z = 0.0f;

// R3 Surface Points matrix
std::vector<std::vector<Point3d>> points = {
    {{-0.5f, 0.0f, -0.5f}, {-0.2f, 0.4f, -0.5f}, {0.2f, 0.4f, -0.5f}},
    {{-0.5f, 0.0f, 0.0f}, {-0.2f, 0.4f, 0.0f}, {0.2f, 0.4f, 0.0f}},
    {{-0.5f, 0.0f, 0.5f}, {-0.2f, 0.4f, 0.5f}, {0.2f, 0.4f, 0.5f}},
};

std::vector<std::vector<Point3d>> transpose(const std::vector<std::vector<Point3d>> &matrix)
{
    std::vector<std::vector<Point3d>> other;
    int pointArrSize = matrix[0].size();
    for (int j = 0; j < pointArrSize; j++)
    {
        other.push_back({});
    }

    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix[i].size(); j++)
        {
            other[j].push_back(matrix[i][j]);
        }
    }
    return other;
}

std::vector<std::vector<Point3d>> transposed = transpose(points);

Point3d applyCastelljau(const std::vector<Point3d> &v_points, const float t)
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

void drawAxis()
{
    glColor3f(GLUT_WHITE_COLOR);
    glBegin(GL_LINES);
    glVertex3f(10.0f, 0.0f, 0.0f);
    glVertex3f(-10.0f, 0.0f, 0.0f);
    glEnd();

    glColor3f(GLUT_WHITE_COLOR);
    glBegin(GL_LINES);
    glVertex3f(0.0f, 10.0f, 0.0f);
    glVertex3f(0.0f, -10.0f, 0.0f);
    glEnd();

    glColor3f(GLUT_WHITE_COLOR);
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 10.0f);
    glVertex3f(0.0f, 0.0f, -10.0f);
    glEnd();
}

void draw()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    glPushMatrix();
    glRotated(angle_x, 1.0f, 0.0f, 0.0f);
    glRotated(angle_y, 0.0f, 1.0f, 0.0f);
    glRotated(angle_z, 0.0f, 0.0f, 1.0f);

    // R3 Polylines
    glColor3f(GLUT_GREEN_COLOR);
    for (int i = 0; i < points.size(); i++)
    {
        glBegin(GL_LINE_STRIP);
        for (int j = 0; j < points[i].size(); j++)
        {
            glVertex3f(points[i][j].x, points[i][j].y, points[i][j].z);
        }
        glEnd();
    }

    for (int i = 0; i < transposed.size(); i++)
    {
        glBegin(GL_LINE_STRIP);
        for (int j = 0; j < transposed[i].size(); j++)
        {
            glVertex3f(transposed[i][j].x, transposed[i][j].y, transposed[i][j].z);
        }
        glEnd();
    }

    drawAxis();

    // Bezier Curve
    glBegin(GL_POINTS);
    glColor3f(GLUT_YELLOW_COLOR);
    for (float t = T_START; t <= T_END; t += T_INCREMENT)
    {
        for (int i = 0; i < points.size(); i++)
        {
            Point3d p = applyCastelljau(points[i], t);
            glVertex3f(p.x, p.y, p.z);
        }
    }
    glVertex3f(1.0f, 0.0f, 0.0f);
    glEnd();

    glPopMatrix();
    glutSwapBuffers();
}

void init()
{
    glClearColor(GLUT_BLUE_COLOR, 1.0f);
    glPointSize(2.0f);
    glOrtho(800, 0, 600, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case KEY_LOWER_A:
    case KEY_UPPER_A:
        angle_y += 5.f;
        break;

    case KEY_LOWER_D:
    case KEY_UPPER_D:
        angle_y -= 5.f;
        break;

    case KEY_LOWER_S:
    case KEY_UPPER_S:
        angle_x += 5.f;
        break;

    case KEY_LOWER_W:
    case KEY_UPPER_W:
        angle_x -= 5.f;
        break;

    case KEY_LOWER_Z:
    case KEY_UPPER_Z:
        angle_z += 5.f;
        break;

    case KEY_LOWER_C:
    case KEY_UPPER_C:
        angle_z -= 5.f;
        break;
    }

    glutPostRedisplay();
}

int main(int argc, char *args[])
{
    glutInit(&argc, args);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutInitWindowSize(800, 600);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Bezier Surface with Castelljau");

    glutDisplayFunc(draw);
    glutKeyboardFunc(keyboard);

    init();

    glutMainLoop();

    return 0;
}