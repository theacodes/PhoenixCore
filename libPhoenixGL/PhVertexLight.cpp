/*

Copyright (c) 2007, Jonathan Wayne Parrott, Denzel Morris

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/


#include "PhVertexLight.h"

using namespace phoenix;

PhVertexLight::PhVertexLight(PhVertexLightSystem* l, const PhVector2d& Position, const PhColor& c)
        : lsys(l), ambient(c), diffuse(c), specular(PhColor(127,127,127,255)), position(Position), catten(1.0f), latten(0.0f), qatten(0.0f), depth(0.0f)
{
    lsys->addLight(this);
}

PhVertexLight::~PhVertexLight()
{
    if (lsys)
    {
        lsys->removeLight(this);
    }
}

void PhVertexLight::setLight(const int& n)
{

    GLfloat light_position[] = { position.getX(), position.getY(), 0.0f, 1.0f };
    GLfloat light_ambient[] = { ambient.getRed()/255.0f, ambient.getGreen()/255.0f, ambient.getBlue()/255.0f, ambient.getAlpha()/255.0f };
    GLfloat light_diffuse[] = { diffuse.getRed()/255.0f, diffuse.getGreen()/255.0f, diffuse.getBlue()/255.0f, diffuse.getAlpha()/255.0f };
    GLfloat light_specular[] = { specular.getRed()/255.0f, specular.getGreen()/255.0f, specular.getBlue()/255.0f, specular.getAlpha()/255.0f };

    glLightfv(GL_LIGHT0+n, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0+n, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0+n, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0+n, GL_POSITION, light_position);

    glLightf(GL_LIGHT0+n, GL_CONSTANT_ATTENUATION, catten);
    glLightf(GL_LIGHT0+n, GL_LINEAR_ATTENUATION, latten);
    glLightf(GL_LIGHT0+n, GL_QUADRATIC_ATTENUATION, qatten);

    glEnable(GL_LIGHT0+n);

}
