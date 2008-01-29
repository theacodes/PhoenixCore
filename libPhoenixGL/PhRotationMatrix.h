#ifndef PHROTATIONMATRIX_H
#define PHROTATIONMATRIX_H

#include <math.h>

namespace phoenix
{
    //pre-declaration of vector & polygon class.
    class PhVector2d;

    //! 2D Rotation Matrix Class
    /*!
        Provides a fast and efficient way to rotate points.
        \note This is generally only used inside PhoenixGL, for rotation of vectors.
        \note Only ambigious operations are documented.
    */
    class PhRotationMatrix
    {

    public:

        //! Constructor.
        /*!
        	Creates an identity matrix (1,0,0,1)
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
        virtual ~PhRotationMatrix();

        //! Set rotation.
        /*!
            \param rad The angle of rotation in radians.
            \sa getRotation()
        */
        void setRotation(float rad);

        //! Get rotation.
        /*!
            \return The angle of rotation in radians.
            \sa setRotation()
        */
        float getRotation();

        //! Matrix access operator.
        /*!
            \return An element in the matrix.
            \param row The row of the element.
            \param col The column of the element.
        */
        float& operator()(const int row, const int col);

        //! Element access operator.
        /*!
            Allows you to access the matrix as a one-dimensional array.
            \return An element in the Matrix.
            \param x The index of the element.
        */
        float& operator[](const int x);

        PhRotationMatrix operator+(PhRotationMatrix& other);
        PhRotationMatrix operator-(PhRotationMatrix& other);
        PhRotationMatrix operator*(PhRotationMatrix& other);
        PhRotationMatrix operator*(float scalar);
        //! Vector multiplication operation.
        /*!
            Essentially rotates the given vector by this matrix.
            \note This is mathematically incorrect, the vector should be the left-hand operand, and the matrix
            should be the right had operand. This is due to matrix multiplication rules. However we're not bound
            by that.
            \return The rotated vector.
            \param other The vector to rotate.
        */
        PhVector2d operator*(PhVector2d& other);
        PhRotationMatrix operator/(PhRotationMatrix& other);
        PhRotationMatrix operator/(float scalar);

        PhRotationMatrix& operator+=(PhRotationMatrix& other);
        PhRotationMatrix& operator-=(PhRotationMatrix& other);
        PhRotationMatrix& operator*=(PhRotationMatrix& other);
        PhRotationMatrix& operator*=(float scalar);
        PhRotationMatrix& operator/=(PhRotationMatrix& other);
        PhRotationMatrix& operator/=(float scalar);

        //! Determinant.
        /*!
            \return The determinant of the matrix.
            \note This is used by the inverse() function.
        */
        float determinant();

        //! Inverse.
        /*!
            \return The multiplicative inverse of this matrix.
            \note This is used by the division operators.
        */
        PhRotationMatrix inverse();

        bool operator==(PhRotationMatrix& other);
        bool operator!=(PhRotationMatrix& other);

    protected:

        float Elements[4];

    private:
    };

}

/*Vector class has to be defined before the source*/
#include "PhVector2d.h"

#endif // PHROTATIONMATRIX_H
