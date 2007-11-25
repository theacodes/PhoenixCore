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

#include "PhRect.h"

using namespace phoenix;

////////////////////////////////////////////////////////////////////////////////
// Construct & set
////////////////////////////////////////////////////////////////////////////////

PhRect::PhRect()
{
    set(0.0f,0.0f,0.0f,0.0f);
}

PhRect::PhRect(float a, float b, float c, float d)
{
    set(a,b,c,d);
}

void PhRect::set (float a, float b, float c, float d)
{
    x=a;
    y=b;
    w=c;
    h=d;
}

////////////////////////////////////////////////////////////////////////////////
// get and set methods
////////////////////////////////////////////////////////////////////////////////

float PhRect::getX()
{
    return x;
}

float PhRect::getY()
{
    return y;
}

float PhRect::getHeight()
{
    return h;
}

float PhRect::getWidth()
{
    return w;
}

void PhRect::setX(float a)
{
    x=a;
}

void PhRect::setY(float b)
{
    y=b;
}

void PhRect::setHeight(float c)
{
    h=c;
}

void PhRect::setWidth(float d)
{
    w=d;
}

PhRect PhRect::operator= (const PhRect other)
{
    x = other.x;
    y = other.y;
    w = other.w;
    h = other.h;
    return *this;
}

