/**
 * DDA Algorithm
 * 
 * Compile in root:
 * g++ wrappers/painter/Painter.cpp 1.DDA/main.cpp -lGL -lGLU -lglut
 * 
 * Compile in 1.DDA:
 * g++ ../wrappers/painter/Painter.cpp main.cpp -lGL -lGLU -lglut
 * 
 */

#include <iostream>
#include <math.h>
#include "../wrappers/painter/Painter.h"

enum Axis
{
   X,
   Y
};

struct Point
{
   float x;
   float y;
};

void printDDALine(const Point &a, const Point &b)
{
   int dx, dy, steps;
   float x, y, xInc, yInc;
   Axis longAxis;

   dx = b.x - a.x;
   dy = b.y - a.y;

   if (abs(dx) > abs(dy))
   {
      steps = abs(dx);
      longAxis = X;
   }
   else
   {
      steps = abs(dy);
      longAxis = Y;
   }

   xInc = (float)dx / (float)steps;
   yInc = (float)dy / (float)steps;

   x = a.x;
   y = a.y;

   while ((longAxis == X ? x <= b.x : y <= b.y))
   {
      Painter::Point(round(x), round(y));
      x += xInc;
      y += yInc;
   }
}

int main(int argc, char **argv)
{
   Point a = {4.0f, 5.0f};
   Point b = {400.0f, 500.0f};

   std::cout << "Point A: ";
   std::cin >> a.x >> a.y;

   std::cout << "Point B: ";
   std::cin >> b.x >> b.y;

   Painter::Window("DDA Algorithm", 500, 500, argc, argv);
   printDDALine(a, b);
   Painter::StartLoop();
}