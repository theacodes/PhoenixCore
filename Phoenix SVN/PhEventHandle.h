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

#include "PhVector2d.h"

namespace phoenix
{

    //! Event handler.
    /*!
        Provides a simple interface to the keyboard, mouse, and other system events.
        The event handler uses SDL key definitions,
        for a list of acceptable key definitions, please see the SDL documentation page located at
        <a href="http://www.libsdl.org/cgi/docwiki.cgi/SDLKey">this website</a>
    */
    class PhEventHandler
    {

    private:

        //! Array to store key info.
        int keys[512];

        //! Array to store mouse info.
        int mousebutton[16];

        //!array to store info on if a key was just pressed.
        int keysdown[512];

        //!array to store info on if a mouse button was just pressed.
        int mousebuttondown[16];

        //!if the user "X"ed out of the window, this is true.
        bool quit;

        //!For catching events.
        SDL_Event event;

        //!stores the mouse's position.
        PhVector2d mousepos;

    public:

        //! Construct.
        PhEventHandler();

        //! Update events.
        /*!
            This polls the window manager for new events, this is always handled by the render system.
        */
        void updateEvents();

        //! Get key.
        /*!
            Gets the state of a current key, true if it is down.
            \param a Key to get the state of.
            \return State of the given key.
            \sa getKeyPressed()
        */
        bool getKey(int a);

        //! Get pressed.
        /*!
            Gets if a get was just pressed.
            \param a Key to get the state of.
            \return True if the key was just pressed.
            \sa getKey()
        */
        bool getKeyPressed(int a);

        //! Get mouse position.
        /*!
            \return A vector that represents the mouse's position relative to the top of the window.
        */
        PhVector2d getMousePosition();

        //! Get mouse button
        /*!
            Gives the state of the given mouse button.
            \param a Button to get the state of.
            \return State of the given button.
            \sa getMouseButtonPressed()
        */
        bool getMouseButton(int a);

        //! Get mouse button pressed
        /*!
            Returns if the mouse button was just pressed.
            \param a Button to get the state of.
            \return True if the mouse button was just pressed.
            \sa getMouseButton()
        */
        bool getMouseButtonPressed(int a);

        //! Return quit.
        /*!
            \return True if the user closed the window.
        */
        bool returnQuit();

    };

}

#endif
