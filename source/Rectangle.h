/*

Copyright (c) 2009, Jonathan Wayne Parrott

Please see the license.txt file included with this source
distribution for more information.

*/

#ifndef __PHOENIXRECT_H__
#define __PHOENIXRECT_H__

#include "Polygon.h"

namespace phoenix
{

    //! Rectangle class.
    /*!
        Simple class that represents a rectangle. Rectangles have a position (x and y) and
		dimensions ( width and height ).
        \sa phoenix::RenderSystem::drawRectangle, pheonix::RenderSystem::drawTexturePart
    */
    class Rectangle
    {

    public:

        //! Blank Constructor.
        Rectangle()
                : position(0,0), dimensions(0,0)
        {
        }

        //! Standard Constructor
        /*!
            Creates a rectangle with the given position and dimensions.
            \param p Position of the rectangle.
            \param d Dimensions of the rectangle.
        */
        Rectangle( const Vector2d& p, const Vector2d& d)
            : position(p), dimensions(d)
        {
        }

        //! Lazy Constructor.
        /*!
            Makes a rectangle with the given dimensions.
            \param a X
            \param b Y
            \param c Width
            \param d Height
        */
        Rectangle( float a, float b, float c, float d)
                : position(a,b), dimensions(c,d)
        {
        }

        //! Implicit conversion from Polygon
        /*!
        	Makes this rectangle a bounding box of the given polygon.
        */
        Rectangle(const Polygon& other);

		//! Destructor
		virtual ~Rectangle() {}

        //! Get Position.
        inline const Vector2d& getPosition() const
        {
            return position;
        }

        //! Set Position.
        inline void setPosition( const Vector2d& p )
        {
            position = p;
        }

        //! Get Dimensions
        inline const Vector2d& getDimensions() const
        {
            return dimensions;
        }

        //! Set Dimensions
        inline void setDimensions( const Vector2d& d )
        {
            dimensions = d;
        }

        //! Get X.
        inline const float getX() const
        {
            return position.getX();
        }

        //! Get Y.
        inline const float getY() const
        {
            return position.getY();
        }

        //! Get Height.
        inline const float getHeight() const
        {
            return dimensions.getY();
        }

        //! Get Width.
        inline const float getWidth() const
        {
            return dimensions.getX();
        }

        //! Set X.
        inline void setX(float a)
        {
            position.setX(a);
        }

        //! Set Y.
        inline void setY(float b)
        {
            position.setY(b);
        }

        //! Set Width.
        inline void setWidth(float d)
        {
            dimensions.setX(d);
        }

        //! Set Height.
        inline void setHeight(float c)
        {
            dimensions.setY(c);
        }

	private:

        //! Position
        Vector2d position;

        //! Dimensions
        Vector2d dimensions;

    };

} //namespace phoenix

#endif //__PHOENIXRECT_H__
