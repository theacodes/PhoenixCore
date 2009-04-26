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
	: x(0), y(0), w(0), h(0)
{
}

PhRect::PhRect(const float& a, const float& b, const float& c, const float& d)
	: x(a), y(b), w(c), h(d)
{
}

PhRect::PhRect( const PhPolygon& other )
{
	if( other.getVertexCount() >= 3 )
	{
		float minx=INFINITY,miny=INFINITY,maxx=-INFINITY,maxy=-INFINITY;

		for(unsigned int i = 0; i < other.getVertexCount(); ++i)
		{
			PhVector2d vertex = other.getPosition() + other.getVertex(i);
			if( vertex.getX() < minx ) minx = vertex.getX();
			if( vertex.getY() < miny ) miny = vertex.getY();
			if( vertex.getX() > maxx ) maxx = vertex.getX();
			if( vertex.getY() > maxy ) maxy = vertex.getY();
		}
		x = minx;
		y = miny;
		w = maxx - minx;
		h = maxy - miny;
	}
	else
	{
		*this = PhRect();
	}
}

void PhRect::set (const float& a, const float& b, const float& c, const float& d)
{
    x=a;
    y=b;
    w=c;
    h=d;
}

////////////////////////////////////////////////////////////////////////////////
// get and set methods
////////////////////////////////////////////////////////////////////////////////

const float& PhRect::getX() const
{
    return x;
}

const float& PhRect::getY() const
{
    return y;
}

const float& PhRect::getHeight() const
{
    return h;
}

const float& PhRect::getWidth() const
{
    return w;
}

void PhRect::setX(const float& a)
{
    x=a;
}

void PhRect::setY(const float& b)
{
    y=b;
}

void PhRect::setHeight(const float& c)
{
    h=c;
}

void PhRect::setWidth(const float& d)
{
    w=d;
}

const PhRect& PhRect::operator= (const PhRect& other)
{
    x = other.x;
    y = other.y;
    w = other.w;
    h = other.h;
    return *this;
}

