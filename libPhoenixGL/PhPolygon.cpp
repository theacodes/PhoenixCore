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

#include "PhPolygon.h"

using namespace phoenix;

PhPolygon::PhPolygon()
        : vertcount(0), pos(0,0), radius(0.0f)
{
}

PhPolygon::PhPolygon(PhVector2d a)
        : vertcount(0), pos(a), radius(0.0f)
{
}

PhPolygon::~PhPolygon()
{
    verts.clear();
}

void PhPolygon::clear()
{
    vertcount = 0;
    pos = PhVector2d(0,0);
    radius = 0.0f;
    verts.clear();
}

PhVector2d PhPolygon::getPosition()
{
    return pos;
}

void PhPolygon::setPosition(PhVector2d a)
{
    pos = a;
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
// Although this shold be "addVertex" and "addPoint" the names are misleading
// The class does not automatically sort the vectors by angle.
// so you're actually "pushing" the vertex or point to the back of the stack
// of vectors on the polygon, the same way you push data into a std::vector
////////////////////////////////////////////////////////////////////////////////

void PhPolygon::pushVertex(PhVector2d a)
{
    verts.push_back(a);
    vertcount+=1;
    if (a.getMagnitude()>radius)
    {
        radius = a.getMagnitude();
    }
}

void PhPolygon::pushPoint(PhVector2d a)
{
    verts.push_back( a-pos );
    vertcount+=1;
    if ((a-pos).getMagnitude()>radius)
    {
        radius = (a-pos).getMagnitude();
    }

}

int PhPolygon::getVertexCount()
{
    return vertcount;
}

PhVector2d PhPolygon::getVertex(int a)
{
    if (a < vertcount)
    {
        return verts[a];
    }
    return verts[0];
}

void PhPolygon::setVertex(int a, PhVector2d v)
{
    if (a < vertcount)
    {
        verts[a] = v;
    }
}

float PhPolygon::getRadius()
{
    return radius;
}

void PhPolygon::rotate(const float& rad)
{
    PhRotationMatrix m(rad);
    rotate(m);
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
    vertcount = other.vertcount;
    verts = other.verts;
    pos = other.pos;
    radius = other.radius;
    return *this;
}

bool PhPolygon::operator== (PhPolygon other)
{
    if (other.vertcount == vertcount&&other.pos == pos&&other.radius == radius)
    {
        for (int i = 0; i < vertcount; i++)
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

PhPolygon PhPolygon::operator* (float scalar)
{
    PhPolygon temp = *this;
    temp.rotate(scalar);
    return temp;
}

PhPolygon& PhPolygon::operator*= (float scalar)
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
