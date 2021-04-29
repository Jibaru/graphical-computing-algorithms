/* 
 * Painter Wrapper
 *
 * This program use
 * OpenGL
 * http://www.opengl.org/
 * 
 * GLUT:
 * https://www.opengl.org/resources/libraries/glut/
 * 
 */

#ifndef _PAINTER_H_
#define _PAINTER_H_

namespace Painter
{

    struct Color
    {
        float R;
        float G;
        float B;
    };

    //Color RED_COLOR = {1.0f, 0.0f, 0.0f};

    void Window(const char *title, const float &width, const float &height, int &argc, char **argv);
    void StartLoop();
    void Point(const float x, const float y);
    void Display();
}

#endif /* PAINTER_H */