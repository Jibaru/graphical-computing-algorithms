/**
 * Bresenham Algorithm
 * 
 * Compile in root:
 * g++ wrappers/painter/Painter.cpp 2.Bresenham/main.cpp -lGL -lGLU -lglut
 * 
 * Compile in 1.DDA:
 * g++ ../wrappers/painter/Painter.cpp main.cpp -lGL -lGLU -lglut
 * 
 */

#include <iostream>
#include <math.h>
#include "../wrappers/painter/Painter.h"

struct NaturalPoint
{
    int x;
    int y;
};

void printBresenhamLine(const NaturalPoint &a, const NaturalPoint &b)
{
    int dx, dy, steps, k;
    int x, y, xIncI, yIncI, xIncR, yIncR;
    int av, avR, avI;

    dx = b.x - a.x;
    dy = b.y - a.y;

    if (dy >= 0)
    {
        yIncI = 1;
    }

    if (dx >= 0)
    {
        xIncI = 1;
    }
    else
    {
        dx = -dx;
        xIncI = -1;
    }

    if (dx >= dy)
    {
        yIncR = 0;
        xIncR = xIncI;
    }
    else
    {
        xIncR = 0;
        yIncR = yIncI;

        k = dx;
        dx = dy;
        dy = k;
    }

    x = a.x;
    y = a.y;

    avR = 2 * dy;
    av = avR - dx;
    avI = av - dx;

    do
    {
        Painter::Point(x, y);
        if (av >= 0)
        {
            x += xIncI;
            y += yIncI;
            av += avI;
        }
        else
        {
            x += xIncR;
            y += yIncR;
            av += avR;
        }
    } while (x < b.x);
}

int main(int argc, char **argv)
{
    NaturalPoint a = {0, 0};
    NaturalPoint b = {0, 0};

    std::cout << "Point A: ";
    std::cin >> a.x >> a.y;

    std::cout << "Point B: ";
    std::cin >> b.x >> b.y;

    Painter::Window("DDA Algorithm", 500, 500, argc, argv);
    printBresenhamLine(a, b);
    Painter::StartLoop();
}