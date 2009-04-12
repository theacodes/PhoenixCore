#include "PhVector2d.h"

using namespace phoenix;

PhVector2d::PhVector2d(): x(0), y(0)
{

}

PhVector2d::PhVector2d(float a, float b): x(a), y(b)
{

}

PhVector2d::~PhVector2d()
{

}

PhVector2d& PhVector2d::operator = (const PhVector2d &rvalue)
{
	x = rvalue.x;
	y = rvalue.y;

	return *this;
}

PhVector2d& PhVector2d::operator+=(const PhVector2d &rvalue)
{

	x += rvalue.x;
	y += rvalue.y;

	return *this;
}

PhVector2d& PhVector2d::operator-=(const PhVector2d &rvalue)
{

	x -= rvalue.x;
	y -= rvalue.y;

	return *this;
}

const PhVector2d PhVector2d::operator+(const PhVector2d &rvalue) const
{
	return PhVector2d(*this) += rvalue;
}

const PhVector2d PhVector2d::operator-(const PhVector2d &rvalue) const
{
	return PhVector2d(*this) -= rvalue;
}

const PhVector2d PhVector2d::operator-(void) const
{
	return PhVector2d(0,0) - PhVector2d(*this);
}

const PhVector2d PhVector2d::operator+(const float &rvalue) const
{
	return PhVector2d(*this) + PhVector2d(rvalue,rvalue);
}
const PhVector2d PhVector2d::operator-(const float &rvalue) const
{
	return PhVector2d(*this) - PhVector2d(rvalue,rvalue);
}
const PhVector2d PhVector2d::operator*(const float &rvalue) const
{
	return PhVector2d( x * rvalue, y * rvalue );
}
const PhVector2d PhVector2d::operator/(const float &rvalue) const
{
	return PhVector2d( x / rvalue, y / rvalue );
}

PhVector2d& PhVector2d::operator+=(const float &rvalue)
{
	(*this) = (*this) + rvalue;
	return *this;
}

PhVector2d& PhVector2d::operator-=(const float &rvalue)
{
	(*this) = (*this) - rvalue;
	return *this;
}

PhVector2d& PhVector2d::operator*=(const float &rvalue)
{
	(*this) = (*this) * rvalue;
	return *this;
}

PhVector2d& PhVector2d::operator/=(const float &rvalue)
{
	(*this) = (*this) / rvalue;
	return *this;
}


bool PhVector2d::operator== (const PhVector2d &rvalue) const
{
	if( x == rvalue.x && y == rvalue.y )
	{
		return true;
	}
	return false;
}

bool PhVector2d::operator!= (const PhVector2d &rvalue) const
{
	return !(*this == rvalue);
}

const float PhVector2d::operator*(const PhVector2d &rvalue) const
{
	return (x*rvalue.x) + (y*rvalue.y);
}

const float PhVector2d::operator^(const PhVector2d &rvalue) const
{
	return (x * rvalue.y) - (y * rvalue.x);
}

const PhVector2d phoenix::operator*(const float &lvalue, const PhVector2d &rvalue)
{
	return rvalue * lvalue;
}

//! Hahaha.

const float PhVector2d::normalize(void)
{
    float fLength = getMagnitude();

    if (fLength == 0.0f)
        return 0.0f;

    (*this) /= fLength;

    return fLength;
}

const float PhVector2d::getMagnitude() const
{
    return sqrt( x*x + y*y );
}

const float PhVector2d::getMagnitudeSquared() const
{
    return (x*x + y*y);
}

//projection
const PhVector2d PhVector2d::project(const PhVector2d& b)
{
    PhVector2d v;
    v.x = (*this)*b * b.x;
    v.y = (*this)*b * b.y;
    return v;
}

const PhVector2d PhVector2d::getDirection(void) const
{
    PhVector2d Temp(*this);

    Temp.normalize();

    return Temp;
}

const float PhVector2d::getAngle(const PhVector2d& xE) const
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

const PhVector2d& PhVector2d::rotate(const float& angle)
{
    float tx = x;
    x =  x * cos(-angle) - y * sin(-angle);
    y = tx * sin(-angle) + y * cos(-angle);
    return *this;
}

const PhVector2d PhVector2d::operator * (const PhRotationMatrix& other) const
{
    return other * PhVector2d(*this);
}

const PhVector2d& PhVector2d::operator *= (const PhRotationMatrix& other)
{
    *this = *this * other;
    return *this;
}
