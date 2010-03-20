/*

Copyright (c) 2009, Jonathan Wayne Parrott

Please see the license.txt file included with this source
distribution for more information.

*/

#ifndef __PHOENIXERC__
#define __PHOENIXERC__

#include <string>
#include <GL/glfw.h>
#include "config.h"
#include "Keys.h"
#include "Vector2d.h"

namespace phoenix
{

    //! Event receiver.
    /*!
        Provides a simple interface to the keyboard, mouse, and other system events. This
        is a completely static class. It is only required that the window manager register all it's callbacks
		upon creation.
        \note WindowManager registers the state callbacks to glfw, therefore an instance of WindowManager must exist before this class will work.
    */
    class EventReceiver
    {

    public:

        //! Constructor
        /*!
            No parameters are required to construct an Event Receiver.
        */
        EventReceiver();

        //! Update events.
        /*!
            Polls the window manager for new events, this is always handled automatically by WindowManager::swapBuffers().
        */
        static void updateEvents();

		//! Keyboard callback
		/*!
			Used by GLFW
		*/
        static void KeyboardCallback( int key, int action );

		//! Character callback
		/*!
			Used by GLFW
		*/
		static void CharacterCallback( int key, int action );

        //! Mousebutton callback
		/*!
			Used by GLFW
		*/
        static void MouseButtonCallback( int key, int action );

        //! Mouse position callback
		/*!
			Used by GLFW
		*/
        static void MousePosCallback( int x, int y ) { mousepos = Vector2d( (float) x, (float) y ); }

        //! Window callback
		/*!
			Used by GLFW
		*/
        inline static int WindowCloseCallback() { quit = true; return GL_TRUE; }

        //! Mouse wheel callback
		/*!
			Used by GLFW
		*/
        inline static void MouseWheelPosCallback( int pos ) { mousewheelpos = pos;}

        //! Gets the state of the given key, true if it is down.
        inline static bool getKey(Key _k) { return keys[_k]; }

        //! Checks if a key was just pressed.
        inline static bool getKeyPressed(Key _k) { return (keysdown[_k]&&keys[_k]); }

        //! Checks if a key was just released.
        inline static bool getKeyReleased(Key _k) { return (keysdown[_k]&&(!keys[_k])); }

		//! Get the current keyboard string.
		/*!
			The event handler keeps track of the characters typed by the user
			via the keyboard. It also tracks the backspace key.
		*/
		inline static const std::string& getKeyboardString(){ return keyboardstring; }

		//! Set the current keyboard string.
		inline static void setKeyboardString( const std::string& _s ){ keyboardstring = _s; }

        //! Get mouse position.
        /*!
            \returns A vector that represents the mouse's position relative to the top left corner of the window.
        */
        inline static const Vector2d& getMousePosition() { return mousepos; }

        //! Get a mouse button state, true if it is down.
        inline static bool getMouseButton(MouseButton _b) { return mousebutton[_b]; }

        //! Check if a mouse button was just pressed.
        inline static bool getMouseButtonPressed(MouseButton _b) { return mousebutton[_b]&&mousebuttondown[_b]; }

        //! Check if a mouse button was just released.
        inline static bool getMouseButtonReleased(MouseButton _b) { return (!mousebutton[_b])&&mousebuttondown[_b]; }

        //! Get mouse wheel position, the amount the wheel was turned on its axis.
        inline static int getMouseWheelPosition() { return mousewheelpos; }

        //! True if the user has closed the window.
        inline static bool getWindowClosed() { return quit; }


	private:

        //! Array to store key state info.
        static bool keys[512];

		//! Array to store mouse state info.
        static bool mousebutton[16];

        //!array to store info on if a key was just pressed or released.
        static bool keysdown[512];

		//!string to store keyboard input
		static std::string keyboardstring;

        //!array to store info on if a mouse button was just pressed or released.
        static bool mousebuttondown[16];

        //!if the user "X"ed out of the window, this is true.
        static bool quit;

        //!stores the mouse's position.
        static Vector2d mousepos;

        //!stores the mouse's wheel position
        static int mousewheelpos;

    };

} //namespace phoenix

#endif //__PHOENIXERC__
