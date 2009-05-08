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

#ifndef PHROTATIONMATRIX_H
#define PHROTATIONMATRIX_H

#include <math.h>

namespace phoenix
{
    //pre-declaration of vector & polygon class.
    class PhVector2d;

    //! 2D Rotation Matrix Class
    /*!
        Provides a fast and efficient way to rotate vectors and polygons.
        \note This is generally only used inside PhoenixGL, for rotation of vectors.
        \note Only ambigious operations are documented.
    */
    class PhRotationMatrix
    {

    public:

        //! Constructor.
        /*!
        	Creates an identity matrix ([1,0],[0,1])
        */
        PhRotationMatrix();

        //! Constructor.
        /*!
        	Creates a matrix with given elements.
        	\param a Element[0,0].
        	\param b Element[0,1].
        	\param c Element[1,0].
        	\param d Element[1,1].
        */
        PhRotationMatrix( const float& a, const float& b, const float& c, const float& d);

        //! Constructor.
        /*!
        	Creates a rotation matrix with the given angle. (Most common).
        	\param a The angle (in radians).
        */
        PhRotationMatrix( const float& a );

        PhRotationMatrix( const PhRotationMatrix& other ) { (*this) = other; }

        ~PhRotationMatrix();

        //! Get element
        inline const float& getElement( const int& id ) const { return Elements[0]; }

        //! Set element
        inline void setElement( const int& id, const float& val ) { Elements[id] = val; }

        //! Set rotation.
        /*!
            \param rad The angle of rotation in radians.
            \sa getRotation()
        */
        inline void setRotation(const float& rad) { (*this) = PhRotationMatrix(rad); }

        //! Get rotation.
        /*!
            \return The angle of rotation in radians.
            \sa setRotation()
        */
        inline const float getRotation() const { return acos(Elements[0]); }

        //! Element access operator.
        /*!
            Allows you to access the matrix as a one-dimensional array.
            \return An element in the Matrix.
            \param x The index of the element.
        */
        float& operator[](const int& x) { return  Elements[x]; }

        const PhRotationMatrix operator+(const PhRotationMatrix& other) const;
        const PhRotationMatrix operator-(const PhRotationMatrix& other) const;
        const PhRotationMatrix operator*(const PhRotationMatrix& other) const;
        const PhRotationMatrix operator*(const float& scalar) const;

        //! Vector multiplication operation.
        /*!
            Essentially rotates the given vector by this matrix.
            \note This is mathematically incorrect, the vector should be the left-hand operand, and the matrix
            should be the right had operand. This is due to matrix multiplication rules. However we're not bound
            by that.
            \return The rotated vector.
            \param other The vector to rotate.
        */
        const PhVector2d operator*(const PhVector2d& other) const;

        const PhRotationMatrix operator/(const PhRotationMatrix& other) const;
        const PhRotationMatrix operator/(const float& scalar) const;

        const PhRotationMatrix& operator+=(const PhRotationMatrix& other);
        const PhRotationMatrix& operator-=(const PhRotationMatrix& other);
        const PhRotationMatrix& operator*=(const PhRotationMatrix& other);
        const PhRotationMatrix& operator*=(const float& scalar);
        const PhRotationMatrix& operator/=(const PhRotationMatrix& other);
        const PhRotationMatrix& operator/=(const float& scalar);

        //! Determinant.
        /*!
            \return The determinant of the matrix.
            \note This is used by the inverse() function.
        */
        const float getDeterminant() const;

        //! Inverse.
        /*!
            \return The multiplicative inverse of this matrix.
            \note This is used by the division operators.
        */
        const PhRotationMatrix getInverse() const;

        bool operator==(const PhRotationMatrix& other) const;
        bool operator!=(const PhRotationMatrix& other) const;

    protected:

        float Elements[4];

    private:
    };

}

/*Vector class has to be defined before the source*/
#include "PhVector2d.h"

#endif // PHROTATIONMATRIX_H
