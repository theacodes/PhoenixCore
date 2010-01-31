/*

Copyright (c) 2009, Jonathan Wayne Parrott

Please see the license.txt file included with this source
distribution for more information.

*/


#ifndef __PHOENIXCOLOR__
#define __PHOENIXCOLOR__

#include "GL/glfw.h"

namespace phoenix
{

    //! Color.
    /*!
        Class to describe colors.  Colors are stored in component form ( Red, Green, Blue, Alpha) in
        single unsigned-byte intensity values from 0-255.
    */
    class Color
    {

    public:

        //! Constructor.
        Color()
                : red(255), green(255), blue(255), alpha(255)
        {}

        //! Constructor.
        /*!
            \param _r Red component.
            \param _g Green component.
            \param _b Blue component.
            \param _a Alpha component. (default 255)
        */
        Color( unsigned char _r, unsigned char _g, unsigned char _b, unsigned int _a = 255)
                : red(_r), green(_g), blue(_b), alpha(_a)
        {}

        //! Set Red Intensity. (0-255)
        inline void setRed(unsigned char _r)
        {
            red = _r;
        }

        //! Set Green Intensity. (0-255)
        inline void setGreen(unsigned char _g)
        {
            green = _g;
        }

        //! Set Blue Intensity. (0-255)
        inline void setBlue(unsigned char _b)
        {
            blue = _b;
        }

        //! Set Intensity Intensity. (0-255) (Transparent-Opaque)
        inline void setAlpha(unsigned char _a)
        {
            alpha = _a;
        }

        //! Get Red Intensity.
        inline unsigned char getRed() const
        {
            return red;
        }

        //! Get Green Intensity.
        inline unsigned char getGreen() const
        {
            return green;
        }

        //! Get Blue Intensity.
        inline unsigned char getBlue() const
        {
            return blue;
        }

        //! Get Alpha Intensity.
        inline unsigned char getAlpha() const
        {
            return alpha;
        }

        //! Encode to GL color.
        /*!
			This function packs the color into opengl ABGR format.
            This is used by all functions that draw things using indexed lists.
            \return This color in encoded opengl ABGR format.
        */
        inline const unsigned int encode() const
        {
            // Pack the bytes in reverse order for opengl's GL_UNSIGNED_BYTE form for glColorPointer.
            return ( ((unsigned int)(alpha)<<24) |
                     ((unsigned int)(blue)<<16) |
                     ((unsigned int)(green)<<8) |
                     ((unsigned int)(red))
                   );
        }

        //! Decode from GL color.
        inline void decode( unsigned int glcolor )
        {
            alpha = (unsigned char)( glcolor>>24 & 0xFF );
            blue = (unsigned char)( glcolor>>16 & 0xFF );
            green = (unsigned char)( glcolor>>8 & 0xFF );
            red = (unsigned char)( glcolor & 0xFF );
        }

        //! Interpolate.
        /*!
            Interpolates between the two colors by the given percent. Does not modify this color,
            instead returns the interpolated color.
            \param _dest The final color.
            \param _percent What percent to interpolate.
        */
        inline const Color interpolate(const Color& _dest, float _percent) const
		{
            if( _percent > 100.0f ) _percent = 100.0f;
            if( _percent < 0.0f ) _percent = 0.0f;
			Color temp;
			temp.red = red + int( float(_dest.red-red) * _percent/100.0f );
			temp.green = green + int( float(_dest.green-green) * _percent/100.0f );
			temp.blue = blue + int( float(_dest.blue-blue) * _percent/100.0f );
			temp.alpha = alpha + int( float(_dest.alpha-alpha) * _percent/100.0f );
			return temp;
		}

    private:

        unsigned char red,green,blue,alpha;

    };

} //namespace phoenix

#endif // __PHOENIXCOLOR__
