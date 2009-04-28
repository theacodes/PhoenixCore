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

#ifndef PHSOLIDBACKGROUND_H
#define PHSOLIDBACKGROUND_H

#include "PhSceneManager.h"

namespace phoenix
{

    //! Solid background node.
    /*!
        A simple background that consists of a solid color.
        \sa phoenix::PhBackground, phoenix::PhSceneNode
    */
    class PhSolidBackground : public PhSceneNode
    {

    protected:

        //! Color of the background.
        PhColor color;

    public:

        //! Constructor.
        /*!
            Builds the background.
            \param s The pointer to the scene manager used to handle this object.
            \param c The color you want this background to use.
            \param d The depth of the background, default -100.0f
        */
        PhSolidBackground(PhSceneManager* s, PhColor c = PhColor(255,255,255), float d = -100.0f);

        //! Set color.
        /*!
            Sets the color of the background.
            \param c The new color.
            \sa getColor(), color
        */
        void setColor(PhColor c);

        //! Get color.
        /*!
            \return The color of the background.
        */
        PhColor getColor();

        //! Overloaded prerender
        void onPreRender();

        //! Overloaded render
        void onRender();

    };

}

#endif
