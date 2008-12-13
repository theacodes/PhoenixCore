#include "PhRotationMatrix.h"

using namespace phoenix;

/*
     Defualt constructor, indentity matrix.
*/
PhRotationMatrix::PhRotationMatrix()
{
    Elements[0] = 1;
    Elements[1] = 0;
    Elements[2] = 0;
    Elements[3] = 1;
}

/*
    Element based construct.
*/
PhRotationMatrix::PhRotationMatrix(float a, float b, float c, float d)
{
    Elements[0] = a;
    Elements[1] = b;
    Elements[2] = c;
    Elements[3] = d;
}

/*
    Angle based construct
*/
PhRotationMatrix::PhRotationMatrix( float a )
{
    float c = cos(a);
    float s = sin(a);
    Elements[0] = c;
    Elements[1] = -s;
    Elements[2] = s;
    Elements[3] = c;
}

/*
    Construct from other
*/
PhRotationMatrix::PhRotationMatrix(const PhRotationMatrix& other)
{
    (*this) = other;
}

/*
    Dtor
*/
PhRotationMatrix::~PhRotationMatrix()
{
    //dtor
}

void PhRotationMatrix::setRotation(const float& rad)
{
    (*this) = PhRotationMatrix(rad);
}

const float PhRotationMatrix::getRotation() const
{
    return acos(Elements[0]);
}


//////////////////////////////////////////////////////////////////////////////////
//ACCESS OPERATORS
//////////////////////////////////////////////////////////////////////////////////

/*
    Element based acces
*/
float& PhRotationMatrix::operator[](const int& x)
{
    return Elements[x];
}

//////////////////////////////////////////////////////////////////////////////////
//ARITHMATIC OPERATORS
//////////////////////////////////////////////////////////////////////////////////

const PhRotationMatrix PhRotationMatrix::operator+(const PhRotationMatrix& other) const
{
    PhRotationMatrix temp;

    temp[0] = getElement(0) + other.getElement(0);
    temp[1] = getElement(1) + other.getElement(1);
    temp[2] = getElement(2) + other.getElement(2);
    temp[3] = getElement(3) + other.getElement(3);

    return temp;
}

const PhRotationMatrix PhRotationMatrix::operator-(const PhRotationMatrix& other) const
{
    PhRotationMatrix temp;

    temp[0] = getElement(0) - other.getElement(0);
    temp[1] = getElement(1) - other.getElement(1);
    temp[2] = getElement(2) - other.getElement(2);
    temp[3] = getElement(3) - other.getElement(3);

    return temp;
}

const PhRotationMatrix PhRotationMatrix::operator*(const PhRotationMatrix& other) const
{
    PhRotationMatrix temp;

    temp[0] = ( getElement(0) * other.getElement(0) ) + ( getElement(1) * other.getElement(2) );
    temp[1] = ( getElement(0) * other.getElement(1) ) + ( getElement(1) * other.getElement(3) );
    temp[2] = ( getElement(2) * other.getElement(0) ) + ( getElement(3) * other.getElement(2)  );
    temp[3] = ( getElement(2) * other.getElement(1) ) + ( getElement(3) * other.getElement(3)  );

    return temp;
}

const PhRotationMatrix PhRotationMatrix::operator*(const float& scalar) const
{
    PhRotationMatrix temp;

    temp[0] = Elements[0] * scalar;
    temp[1] = Elements[1] * scalar;
    temp[2] = Elements[2] * scalar;
    temp[3] = Elements[3] * scalar;

    return temp;
}

const PhVector2d PhRotationMatrix::operator*(const PhVector2d& other) const
{

    PhVector2d temp;

    temp.setX( ( Elements[0] * other.getX() ) + ( Elements[1] * other.getY() ) );
    temp.setY( ( Elements[2] * other.getX() ) + ( Elements[3] * other.getY() ) );

    return temp;

}

const PhRotationMatrix PhRotationMatrix::operator/(const PhRotationMatrix& other) const
{
    PhRotationMatrix temp(*this);
    PhRotationMatrix inv = other.getInverse();
    return temp * inv;
}

const PhRotationMatrix PhRotationMatrix::operator/(const float& scalar) const
{
    PhRotationMatrix temp;

    temp[0] = Elements[0] / scalar;
    temp[1] = Elements[1] / scalar;
    temp[2] = Elements[2] / scalar;
    temp[3] = Elements[3] / scalar;

    return temp;
}

//////////////////////////////////////////////////////////////////////////////////
//RELATIVE ARTHMATIC OPERATORS
//////////////////////////////////////////////////////////////////////////////////

const PhRotationMatrix& PhRotationMatrix::operator+=( const PhRotationMatrix& other)
{
    (*this) = (*this) + other;
    return (*this);
}

const PhRotationMatrix& PhRotationMatrix::operator-=( const PhRotationMatrix& other)
{
    (*this) = (*this) - other;
    return (*this);
}

const PhRotationMatrix& PhRotationMatrix::operator*=( const PhRotationMatrix& other)
{
    (*this) = (*this) * other;
    return (*this);
}

const PhRotationMatrix& PhRotationMatrix::operator*=( const float& scalar )
{
    (*this) = (*this) * scalar;
    return (*this);
}

const PhRotationMatrix& PhRotationMatrix::operator/=( const PhRotationMatrix& other)
{
    (*this) = (*this) / other;
    return (*this);
}

const PhRotationMatrix& PhRotationMatrix::operator/=( const float& scalar )
{
    (*this) = (*this) / scalar;
    return (*this);
}

//////////////////////////////////////////////////////////////////////////////////
//COMPARISON OPERATORS
//////////////////////////////////////////////////////////////////////////////////

bool PhRotationMatrix::operator==(const PhRotationMatrix& other) const
{
    if (getElement(0) == other.getElement(0) &&
            getElement(1) == other.getElement(1) &&
            getElement(2) == other.getElement(2) &&
            getElement(3) == other.getElement(3))
        return true;
    return false;
}

bool PhRotationMatrix::operator!=(const PhRotationMatrix& other) const
{
    if ((*this==other))
        return false;
    return true;
}

//////////////////////////////////////////////////////////////////////////////////
//MATRIX EXCLUSIVE OPERATORS
//////////////////////////////////////////////////////////////////////////////////

const float PhRotationMatrix::getDeterminant() const
{
    float d1 = Elements[0] + Elements[3];
    float d2 = Elements[1] + Elements[2];
    return (d1 - d2);
}

const PhRotationMatrix PhRotationMatrix::getInverse() const
{

    float det = getDeterminant();
    PhRotationMatrix temp;

    temp[0] = Elements[3];
    temp[1] = -Elements[1];
    temp[2] = -Elements[2];
    temp[3] = Elements[0];

    return temp*(1.0f/det);
}
