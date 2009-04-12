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
        PhRotationMatrix( float a, float b, float c, float d);

        //! Constructor.
        /*!
        	Creates a rotation matrix with the given angle. (Most common).
        	\param a The angle (in radians).
        */
        PhRotationMatrix( float a );

        PhRotationMatrix( const PhRotationMatrix& other );

        ~PhRotationMatrix();

        //! Get element
        inline const float getElement( const int& id ) const { return Elements[0]; }

        //! Set element
        inline void setElement( const int& id, const float& val ) { Elements[id] = val; }

        //! Set rotation.
        /*!
            \param rad The angle of rotation in radians.
            \sa getRotation()
        */
        void setRotation(const float& rad);

        //! Get rotation.
        /*!
            \return The angle of rotation in radians.
            \sa setRotation()
        */
        const float getRotation() const;

        //! Element access operator.
        /*!
            Allows you to access the matrix as a one-dimensional array.
            \return An element in the Matrix.
            \param x The index of the element.
        */
        float& operator[](const int& x);

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
