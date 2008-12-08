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

#include "PhVector2d.h"

using namespace phoenix;

PhVector2d::PhVector2d(float a,float b)
{
    x=a;
    y=b;
}

float PhVector2d::getX()
{
    return x;
}

float PhVector2d::getY()
{
    return y;
}

void PhVector2d::setX(float a)
{
    x=a;
}

void PhVector2d::setY(float a)
{
    y=a;
}

float PhVector2d::normalize(void)
{
    float fLength = getMagnitude();

    if (fLength == 0.0f)
        return 0.0f;

    (*this) /= fLength;

    return fLength;
}

float PhVector2d::getMagnitude()
{
    return sqrt( x*x + y*y );
}

float PhVector2d::getMagnitudeSquared()
{
    return (x*x + y*y);
}

//projection
PhVector2d PhVector2d::project(PhVector2d b)
{
    PhVector2d v;
    v.x = (*this)*b * b.x;
    v.y = (*this)*b * b.y;
    return v;
}

PhVector2d PhVector2d::direction(void)
{
    PhVector2d Temp(*this);

    Temp.normalize();

    return Temp;
}

float PhVector2d::getAngle(PhVector2d xE)
{
    float dot = (*this) * xE;
    float cross = (*this) ^ xE;

    // angle between segments
    float angle = (float) atan2(cross, dot);

    if (angle > 0)
    {
        return angle;
    }
    else
    {
        return (angle)+DegreesToRadians(360.0f);
    }
}

PhVector2d PhVector2d::rotate(float angle)
{
    float tx = x;
    x =  x * cos(-angle) - y * sin(-angle);
    y = tx * sin(-angle) + y * cos(-angle);
    return *this;
}

PhVector2d& PhVector2d::operator /=(const float Scalar)
{
    x /= Scalar;
    y /= Scalar;
    return *this;
}
PhVector2d& PhVector2d::operator *=(const float Scalar)
{
    x *= Scalar;
    y *= Scalar;
    return *this;
}

PhVector2d& PhVector2d::operator +=(const PhVector2d &Other)
{
    x += Other.x;
    y += Other.y;
    return *this;
}
PhVector2d& PhVector2d::operator -=(const PhVector2d &Other)
{
    x -= Other.x;
    y -= Other.y;
    return *this;
}
bool PhVector2d::operator == (const PhVector2d &V)	const
{
    if (x == V.x && y == V.y)
    {
        return true;
    }
    else
    {
        return false;
    }
}
float PhVector2d::operator ^ (const PhVector2d &V)	const
{
    return (x * V.y) - (y * V.x);
} // cross product
float PhVector2d::operator * (const PhVector2d &V)	const
{
    return (x*V.x) + (y*V.y);
} // dot product
PhVector2d PhVector2d::operator * (float  s)			const
{
    return PhVector2d(x*s, y*s);
}

PhVector2d phoenix::operator * (float k, const PhVector2d& V)
{
    return PhVector2d(V.x*k, V.y*k);
}

PhVector2d PhVector2d::operator / (float  s)			const
{
    return PhVector2d(x/s, y/s);
}

PhVector2d PhVector2d::operator + (const PhVector2d &V)	const
{
    return PhVector2d(x+V.x, y+V.y);
}

PhVector2d PhVector2d::operator - (const PhVector2d &V)	const
{
    return PhVector2d(x-V.x, y-V.y);
}

PhVector2d PhVector2d::operator -(void) const
{
    return PhVector2d(-x, -y);
}

PhVector2d PhVector2d::operator * (PhRotationMatrix& other)
{

    PhVector2d temp = *this;
    return other * temp;
}

PhVector2d& PhVector2d::operator *= (PhRotationMatrix& other)
{
    *this = *this * other;
    return *this;
}
