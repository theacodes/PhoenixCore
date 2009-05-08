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

#include "PhPolygon.h"

using namespace phoenix;

PhPolygon::PhPolygon()
	: pos(0,0), radius(0.0f)
{
	verts.clear();
}

PhPolygon::PhPolygon(const PhVector2d& a)
	: pos(a), radius(0.0f)
{
	verts.clear();
}

PhPolygon::PhPolygon(const PhRect& other)
	: radius(0.0f)
{
	pos = PhVector2d(other.getX()+(other.getWidth()/2.0f), other.getY()+(other.getHeight()/2.0f));
	addPoint( PhVector2d( other.getX(), other.getY() ));
	addPoint( PhVector2d( other.getX() + other.getWidth(), other.getY() ));
	addPoint( PhVector2d( other.getX() + other.getWidth(), other.getY()+other.getHeight() ));
	addPoint( PhVector2d( other.getX(), other.getY()+other.getHeight() ));
}

PhPolygon::~PhPolygon()
{
    verts.clear();
}

void PhPolygon::clear()
{
    pos = PhVector2d(0,0);
    radius = 0.0f;
    verts.clear();
}

////////////////////////////////////////////////////////////////////////////////
//push vertex and push point need some explaining
// push vertex pushes a vector directly into the polygon, regardless of the position
// push vertex doesn't care were the polygon is, so PhVector2d(0.0f,10.0f) would
// push an upwards vector into the polygon
// however, push point does care about where the polygon is
// it takes the vector between our position and where the point is and puts it
// onto the polygon. it's the relative function.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Another note about this exception to the naming conventions.
// The class does not automatically sort the vectors by angle.
////////////////////////////////////////////////////////////////////////////////

void PhPolygon::addVertex(const PhVector2d& a)
{
    verts.push_back(a);
    if (a.getMagnitude()>radius)
    {
        radius = a.getMagnitude();
    }
}

void PhPolygon::addPoint(const PhVector2d& a)
{
    verts.push_back( a-pos );
    if ((a-pos).getMagnitude()>radius)
    {
        radius = (a-pos).getMagnitude();
    }

}

void PhPolygon::rotate(const PhRotationMatrix& m)
{
    for (unsigned int i=0;i < verts.size();i++)
    {
        verts[i] = m * verts[i];
    }
}

const PhPolygon& PhPolygon::operator= (const PhPolygon& other)
{
    verts = other.verts;
    pos = other.pos;
    radius = other.radius;
    return *this;
}

const bool PhPolygon::operator== (const PhPolygon& other) const
{
    if (other.pos == pos&&other.radius == radius)
    {
        for (unsigned int i = 0; i < verts.size(); i++)
        {
            if (!(verts[i] == other.verts[i]))
            {
                return false;
            }
        }
        return true;
    }
    return false;
}

const PhPolygon PhPolygon::operator* (const float& scalar) const
{
    PhPolygon temp = *this;
    temp.rotate(scalar);
    return temp;
}

const PhPolygon& PhPolygon::operator*= (const float& scalar)
{
    rotate(scalar);
    return *this;
}

const PhPolygon PhPolygon::operator* (const PhRotationMatrix& other) const
{
    PhPolygon temp = *this;
    temp.rotate(other);
    return temp;
}

const PhPolygon& PhPolygon::operator*= (const PhRotationMatrix& other)
{
    rotate(other);
    return *this;
}
