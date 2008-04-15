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

#ifndef PHOENIXCOL
#define PHOENIXCOL

namespace phoenix
{

    //! Color.
    /*!
        Class to contain colors. Stores a color as RGBA wth values from 0-255.
    */
    class PhColor
    {

    private:

        int red,green,blue,alpha;

    public:

        //! Constructor.
        PhColor();

        //! Constructor.
        /*!
            \param x Red component.
            \param y Green component.
            \param z Blue component.
            \param a Alpha component (default 255)
        */
        PhColor( int x, int y, int z, int a = 255);

        //! Set red.
        /*!
            Sets the red component of the color.
            \param a Value from 0 to 255.
            \sa getRed()
        */
        void setRed(int a);

        //! Set green.
        /*!
            Sets the green component of the color.
            \param a Value from 0 to 255.
            \sa getGreen()
        */
        void setGreen(int a);

        //! Set blue.
        /*!
            Sets the blue. component of the color.
            \param a Value from 0 to 255.
            \sa getBlue()
        */
        void setBlue(int a);

        //! Set alpha.
        /*!
            Sets the alpha component of the color.
            0 being completely transparent, 255 being fully opaque.
            \param a Value from 0 to 255.
            \sa getAlpha().
        */
        void setAlpha(int a);

        //! Get red.
        /*!
            \return The red component of the color.
            \sa setRed()
        */
        int getRed();

        //! Get green.
        /*!
            \return The green component of the color.
            \sa setGreen()
        */
        int getGreen();

        //! Get blue.
        /*!
            \return The blue component of the color.
            \sa setBlue()
        */
        int getBlue();

        //! Get alpha.
        /*!
            \return The alpha component of the color.
            \sa setAlpha()
        */
        int getAlpha();

        //! Set active color.
        /*!
            Makes this color the current active color for drawing.
        */
        void setActiveColor();

        //! To GL color.
        /*!
            This is used by all functions that draw things using indexed lists.
            \return This color in encoded opengl format.
            \sa phoenix::PhRenderSystem::drawIndexedTriangleList()
        */
        int toGLColor();

        //! Interpolate.
        /*!
            Interpolates between the two colors by the given percent. Does not modify this color,
            instead returns the interpolated color.
            \param dest The final color.
            \param percent What percent to interpolate.
        */
        PhColor interpolate(PhColor dest,float percent);

        PhColor& operator = (const PhColor other);

    };

}

#endif
