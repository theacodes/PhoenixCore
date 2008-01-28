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

#ifndef PHOENIXRECT
#define PHOENIXRECT

namespace phoenix
{

    //! Rectangle class.
    /*!
        Simple class that represents a rectangle.
        \sa phoenix::PhRenderSystem::drawRectangle, pheonix::PhRenderSystem::drawTexturePart
    */
    class PhRect
    {

    private:

        //variables for storing the variables
        float x,y,w,h;

    public:

        //! Constructor.
        PhRect();

        //! Constructor.
        /*!
            Makes a rectangle with the given dimensions.
            \param a X
            \param b Y
            \param c Width
            \param d Height
        */
        PhRect(float a, float b, float c, float d);

        //! Set.
        /*!
            Sets the rectangle to the given dimensions.
            \param a X
            \param b Y
            \param c Width
            \param d Height
        */
        void set (float a, float b, float c, float d);

        //! Get X.
        float getX();

        //! Get Y.
        float getY();

        //! Get Height.
        float getHeight();

        //! Get Width.
        float getWidth();

        //! Set X.
        void setX(float a);

        //! Set Y.
        void setY(float b);

        //! Set Height.
        void setHeight(float c);

        //! Set Width.
        void setWidth(float d);

        PhRect operator= (PhRect other);

    };

}

#endif
