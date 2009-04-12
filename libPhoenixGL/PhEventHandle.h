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

#ifndef PHOENIXEHC
#define PHOENIXEHC

#include "GL/glfw.h"
#include "PhKeys.h"
#include "PhVector2d.h"

namespace phoenix
{

    //! Event handler.
    /*!
        Provides a simple interface to the keyboard, mouse, and other system events.
    */
    class PhEventHandler
    {

    private:

        //! Array to store key info.
        static bool keys[512];

        //! Array to store mouse info.
        static bool mousebutton[16];

        //!array to store info on if a key was just pressed.
        static bool keysdown[512];

        //!array to store info on if a mouse button was just pressed.
        static bool mousebuttondown[16];

        //!if the user "X"ed out of the window, this is true.
        static bool quit;

        //!stores the mouse's position.
        static PhVector2d mousepos;

        //!stores the mouse's wheel position
        static int mousewheelpos;

    public:

        //! Construct.
        PhEventHandler();

        //! Update events.
        /*!
            This polls the window manager for new events, this is always handled by the render system.
        */
        void updateEvents();

        static void KeyboardCallback( int key, int action );

        static void MouseButtonCallback( int key, int action );

        static void MousePosCallback( int x, int y );

        static int WindowCloseCallback();

        static void MouseWheelPosCallback( int pos );

        //! Get key.
        /*!
            Gets the state of a current key, true if it is down.
            \param a Key to get the state of.
            \return State of the given key.
            \sa getKeyPressed()
        */
        const bool& getKey(const PhKey& a) const;

        //! Get pressed.
        /*!
            Gets if a get was just pressed.
            \param a Key to get the state of.
            \return True if the key was just pressed.
            \sa getKey()
        */
        const bool& getKeyPressed(const PhKey& a) const;

        //! Get mouse position.
        /*!
            \return A vector that represents the mouse's position relative to the top of the window.
        */
        const PhVector2d& getMousePosition() const;

        //! Get mouse button
        /*!
            Gives the state of the given mouse button.
            \param a Button to get the state of.
            \return State of the given button.
            \sa getMouseButtonPressed()
        */
        const bool& getMouseButton(const PhMouseKey& a) const;

        //! Get mouse button pressed
        /*!
            Returns if the mouse button was just pressed.
            \param a Button to get the state of.
            \return True if the mouse button was just pressed.
            \sa getMouseButton()
        */
        const bool& getMouseButtonPressed(const PhMouseKey& a) const;

        //! Get mouse wheel position.
        /*!
        	Returns the amount the wheel was turned on its
        	axis.
        	\return The amount of rotation.
        */
        const int& getMouseWheelPosition() const;

        //! Return quit.
        /*!
            \return True if the user closed the window.
        */
        const bool& getWindowClosed() const;

    };

}

#endif
