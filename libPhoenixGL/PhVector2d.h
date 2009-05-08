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

#ifndef __PHVECTOR2D_H__
#define __PHVECTOR2D_H__

#include <math.h>
#include "PhRotationMatrix.h"

namespace phoenix
{

    //! Radians to degrees.
    /*!
        Converts radians to degrees, as simple as that.
        \param rad Angle in radians.
        \return Angle in degrees.
        \sa phoenix::DegreesToRadians()
    */
    inline float RadiansToDegrees(float rad)
    {
        const float k = 180.0f / 3.14159265f;
        return rad * k;
    }

    //! Degrees to radians.
    /*!
        Converts degrees to radians, as simple as that.
        \param deg Angle in degrees.
        \return Angle in radians.
        \sa phoenix::RadiansToDegrees()
    */
    inline float DegreesToRadians(float deg)
    {
        const float k = 3.14159265f / 180.0f;
        return deg * k;
    }

    //! 2D Vector class
    /*!
        Provides a fast and efficient way to do vector math.
        \note Only the ambigious operators are documented, the others (such as +, -, +=, etc.) are considered obvious and therefore not documented.
    */
    class PhVector2d
    {
    public:

        PhVector2d();
        PhVector2d(float a, float b);

        inline const float getX() const
        {
            return x;
        }
        inline const float getY() const
        {
            return y;
        }
        inline void setX( const float &a )
        {
            x = a;
        }
        inline void setY( const float &b )
        {
            y = b;
        }

        PhVector2d& operator = (const PhVector2d &rvalue);

        PhVector2d& operator+=(const PhVector2d &rvalue);
        PhVector2d& operator-=(const PhVector2d &rvalue);

        const PhVector2d operator+(const PhVector2d &rvalue) const;
        const PhVector2d operator-(const PhVector2d &rvalue) const;

        const PhVector2d operator+(const float &rvalue) const;
        const PhVector2d operator-(const float &rvalue) const;
        const PhVector2d operator*(const float &rvalue) const;
        const PhVector2d operator/(const float &rvalue) const;

        PhVector2d& operator+=(const float &rvalue);
        PhVector2d& operator-=(const float &rvalue);
        PhVector2d& operator*=(const float &rvalue);
        PhVector2d& operator/=(const float &rvalue);

        const PhVector2d operator-(void) const;

        bool operator == (const PhVector2d &rvalue) const;
        bool operator != (const PhVector2d &rvalue) const;

        //! Dot Product
        const float operator*(const PhVector2d &rvalue) const;

        //! Cross Product
        const float operator^(const PhVector2d &rvalue) const;

        //! Normalization.
        /*!
            Normalizes the vector, as in turns it into a unit-length vector.
            \return The length of the vector before normalization.
        */
        const float normalize();

		//! Magnitude.
        /*!
            \return The magnitude (length) of the vector.
            \sa getManitudeSquared();
        */
        const float getMagnitude() const;

        //! Magnitude squared.
        /*!
            This is much faster than the above because it does not bother to take the square root.
            \return The squared magnitude (length) of the vector.
            \sa getMagnitude();
        */
        const float getMagnitudeSquared() const;

        //! Projection.
        /*!
            Projects this vector onto vector b.
            \param b Vector to project this vector onto
            \return The product of projection.
        */
        const PhVector2d project(const PhVector2d& b);

        //! Direction.
        /*!
            \return A unit-length (normalized) vector with the same angle measure as this one.
        */
        const PhVector2d getDirection(void) const;

        //! Rotate.
        /*!
            Rotates the vector the desired amount.
            \param angle The measure of the angle in radians.
            \return The rotated vector. Note that this vector itself is also rotated.
        */
        const PhVector2d& rotate(const float& angle);

        //! Get angle.
        /*!
            Get the angle measure of the vector relative to the reference vector given. By defualt this is
            <1,0> but it can be changed.
            \param xE The reference vector, by defualt this is <1,0>
            \return The angle between the reference vector and this vector.
        */
        const float getAngle(const PhVector2d& xE = PhVector2d(1.0f,0) ) const;

        //! Matrix multiplication.
        /*!
            Essentially rotates this vector by the matrix.
            \note this is technically mathematically illegal. The matrix should be multiplied by the vector.
            \return The rotated vector.
        */
        const PhVector2d operator * (const PhRotationMatrix& other) const;

        const PhVector2d& operator *= (const PhRotationMatrix& other);

        ~PhVector2d();
    protected:
        float x,y;
    private:
    };

    const PhVector2d operator*(const float &lvalue, const PhVector2d &rvalue);

}

#endif // PHVECTOR2D_H
