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

#ifndef PHOENIXVIEW
#define PHOENIXVIEW

#include "PhRenderSystem.h"

namespace phoenix
{

    //! View class.
    /*!
        Simple view class that simulates a camera looking down on a 2d scene.
        Handles translation, rotation and scaling of the view.
    */
    class PhView
    {

    protected:

        //! Position of the view.
        PhVector2d pos;

        //! Rotation.
        /*!
            Stores the current rotation of the view (In degrees).
        */
        float rot;

        //! Scale factor.
        /*!
            Stores the current scale factor of the scene, 1 is default.
        */
        float scale;

        //! Render system pointer.
        /*!
            pointer to phoenix::PhRenderSystem.
        */
        PhRenderSystem* system;

    public:

        //! Constructor.
        /*!
            \param s A pointer to the phoenix::PhRenderSystem that this view will control
            \param a X of the top-left corner of the view
            \param b Y of the top-left corner of the view
        */
        PhView(PhRenderSystem* s,float a = 0, float b = 0);

        //! Get X function.
        /*!
            \return Simply returns the X value of the view.
        */
        float getX();

        //! Get Y function.
        /*!
            \return Simply returns the Y value of the view.
        */
        float getY();

        //! Get rotation.
        /*!
            \return The current rotation of the view (in degrees).
        */
        float getRotation();

        //! Get position (vector).
        /*!
            Gets the position of the current view as phoenix::PhVector2d().
            \return PhVector2d containing the top-left corner of the view.
        */
        PhVector2d getPosition();

        //! Get scale.
        /*!
            \return Returns the current scale of the view.
        */
        float getScale();

        //! Set X function.
        /*!
            Sets the X value of the top-left corner of the view.
        */
        void setX(float);

        //! Set Y function.
        /*!
            Sets the Y value of the top-left corner of the view.
        */
        void setY(float);

        //! Set position (vector).
        /*!
            Sets the top-left corner of the view.
            \param p A phoenix::PhVector2d representing the new position.
        */
        void setPosition(PhVector2d p);

        //! Set rotation.
        /*!
            Sets the rotation of the view (in degrees).
        */
        void setRotation(float);

        //! Set scale.
        /*!
            Sets the scale factor of the view.
        */
        void setScale(float);

        //! Set GL view
        /*!
            Does the required matrix operations in OpenGL to set the view to this.
        */
        void setGLView();

    };

}

#endif

//Terribly complex, isn't it?
