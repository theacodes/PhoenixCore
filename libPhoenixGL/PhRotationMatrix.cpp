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

void PhRotationMatrix::setRotation(float rad)
{
    (*this) = PhRotationMatrix(rad);
}

float PhRotationMatrix::getRotation()
{
    return acos(Elements[0]);
}


//////////////////////////////////////////////////////////////////////////////////
//ACCESS OPERATORS
//////////////////////////////////////////////////////////////////////////////////

/*
    Row/Column based acces
*/
float& PhRotationMatrix::operator()(const int row, const int col)
{
    return Elements[row * 2 + col];
}

/*
    Element based acces
*/
float& PhRotationMatrix::operator[](const int x)
{
    return Elements[x];
}

//////////////////////////////////////////////////////////////////////////////////
//ARITHMATIC OPERATORS
//////////////////////////////////////////////////////////////////////////////////

PhRotationMatrix PhRotationMatrix::operator+(PhRotationMatrix& other)
{
    PhRotationMatrix temp;

    temp[0] = Elements[0] + other[0];
    temp[1] = Elements[1] + other[1];
    temp[2] = Elements[2] + other[2];
    temp[3] = Elements[3] + other[3];

    return temp;
}

PhRotationMatrix PhRotationMatrix::operator-(PhRotationMatrix& other)
{
    PhRotationMatrix temp;

    temp[0] = Elements[0] - other[0];
    temp[1] = Elements[1] - other[1];
    temp[2] = Elements[2] - other[2];
    temp[3] = Elements[3] - other[3];

    return temp;
}

PhRotationMatrix PhRotationMatrix::operator*(PhRotationMatrix& other)
{
    PhRotationMatrix temp;

    temp[0] = (Elements[0] * other[0] ) + (Elements[1] * other[2] );
    temp[1] = (Elements[0] * other[1] ) + (Elements[1] * other[3] );
    temp[2] = (Elements[2] * other[0] ) + (Elements[3] * other[2] );
    temp[3] = (Elements[2] * other[1] ) + (Elements[3] * other[3] );

    return temp;
}

PhRotationMatrix PhRotationMatrix::operator*(float scalar)
{
    PhRotationMatrix temp;

    temp[0] = Elements[0] * scalar;
    temp[1] = Elements[1] * scalar;
    temp[2] = Elements[2] * scalar;
    temp[3] = Elements[3] * scalar;

    return temp;
}

PhVector2d PhRotationMatrix::operator*(PhVector2d& other){

    PhVector2d temp;

    temp.setX( ( Elements[0] * other.getX() ) + ( Elements[1] * other.getY() ) );
    temp.setY( ( Elements[2] * other.getX() ) + ( Elements[3] * other.getY() ) );

    return temp;

}

PhRotationMatrix PhRotationMatrix::operator/(PhRotationMatrix& other)
{
    PhRotationMatrix temp(*this);
    PhRotationMatrix inv = other.inverse();
    return temp * inv;
}

PhRotationMatrix PhRotationMatrix::operator/(float scalar)
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

PhRotationMatrix& PhRotationMatrix::operator+=( PhRotationMatrix& other)
{
    (*this) = (*this) + other;
    return (*this);
}

PhRotationMatrix& PhRotationMatrix::operator-=( PhRotationMatrix& other)
{
    (*this) = (*this) - other;
    return (*this);
}

PhRotationMatrix& PhRotationMatrix::operator*=( PhRotationMatrix& other)
{
    (*this) = (*this) * other;
    return (*this);
}

PhRotationMatrix& PhRotationMatrix::operator*=( float scalar )
{
    (*this) = (*this) * scalar;
    return (*this);
}

PhRotationMatrix& PhRotationMatrix::operator/=( PhRotationMatrix& other)
{
    (*this) = (*this) / other;
    return (*this);
}

PhRotationMatrix& PhRotationMatrix::operator/=( float scalar )
{
    (*this) = (*this) / scalar;
    return (*this);
}

//////////////////////////////////////////////////////////////////////////////////
//COMPARISON OPERATORS
//////////////////////////////////////////////////////////////////////////////////

bool PhRotationMatrix::operator==(PhRotationMatrix& other)
{
    if (Elements[0] == other[0] &&
            Elements[1] == other[1] &&
            Elements[2] == other[2] &&
            Elements[3] == other[3])
        return true;
    return false;
}

bool PhRotationMatrix::operator!=(PhRotationMatrix& other)
{
    if ((*this==other))
        return false;
    return true;
}

//////////////////////////////////////////////////////////////////////////////////
//MATRIX EXCLUSIVE OPERATORS
//////////////////////////////////////////////////////////////////////////////////

float PhRotationMatrix::determinant()
{
    float d1 = Elements[0] + Elements[3];
    float d2 = Elements[1] + Elements[2];
    return (d1 - d2);
}

PhRotationMatrix PhRotationMatrix::inverse()
{

    float det = determinant();
    PhRotationMatrix temp;

    temp[0] = Elements[3];
    temp[1] = -Elements[1];
    temp[2] = -Elements[2];
    temp[3] = Elements[0];

    return temp*(1.0f/det);
}
