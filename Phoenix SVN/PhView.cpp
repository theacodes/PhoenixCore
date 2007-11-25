/*

Copyright (c) 2007, Jonathan Wayne Parrott.

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

#include "PhView.h"

using namespace phoenix;

////////////////////////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////////////////////////

PhView::PhView(PhRenderSystem* s, float a, float b)
{
    pos = PhVector2d(a,b);
    rot = 0.0f;
    system = s;
    scale = 1.0f;
}

////////////////////////////////////////////////////////////////////////////////
// Get X and Y functions
////////////////////////////////////////////////////////////////////////////////

float PhView::getX()
{
    return pos.getX();
}

float PhView::getY()
{
    return pos.getY();
}

float PhView::getRotation()
{
    return rot;
}

float PhView::getScale()
{
    return scale;
}

PhVector2d PhView::getPosition()
{
    return pos;
}

////////////////////////////////////////////////////////////////////////////////
// Set X and Y functions
////////////////////////////////////////////////////////////////////////////////

void PhView::setX(float a)
{
    pos.setX(a);
}

void PhView::setY(float a)
{
    pos.setY(a);
}

void PhView::setRotation(float a)
{
    rot = a;
}

void PhView::setScale(float a)
{
    scale = a;
}

void PhView::setPosition(PhVector2d p)
{
    pos = p;
}

////////////////////////////////////////////////////////////////////////////////
// Set the view to this.
////////////////////////////////////////////////////////////////////////////////

void PhView::setGLView()
{

    float x = pos.getX();
    float y = pos.getY();

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    glScalef(scale,scale,1.0f);

    glTranslatef(-x + (system->getScreenSize().getX()/2.0f),-y + (system->getScreenSize().getY()/2.0f),0.0f);

    glRotatef(rot,0.0f,0.0f,1.0f);

    glTranslatef(-(system->getScreenSize().getX()/2.0f),-(system->getScreenSize().getY()/2.0f),0.0f);

}
