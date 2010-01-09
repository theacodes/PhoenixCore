/*

Copyright (c) 2009, Jonathan Wayne Parrott

Please see the license.txt file included with this source
distribution for more information.

*/

#ifndef __PHWINDOWMANAGER_H__
#define __PHWINDOWMANAGER_H__

#include <GL/glfw.h>
#include <boost/function.hpp>
#include "EventReceiver.h"
#include "Vector2d.h"

namespace phoenix
{

//! Window Manager
/*!
	This class is responsible for window management activities such as creating and closing the window,
	making an opengl context, and setting the caption. This class is completely static and automatically
	sets up EventReceiver.
*/
class WindowManager
{
public:

	WindowManager()
	{}

	/*!
		Creates a new window and initializes OpenGL. Also sets up callbacks for
		key events.
		\param _sz The size of the window.
		\param _f Fullscreen.
	*/
	static void open( Vector2d _sz = Vector2d( 640, 480 ), bool _f = false );

	/*!
		Closes and terminates the window.
	*/
	inline static void close()
	{
	    glfwCloseWindow();
		glfwTerminate();
	}

	//! Set window caption.
    inline static void setWindowCaption(const std::string& _str) { glfwSetWindowTitle(_str.c_str()); }

	//! Set screen size
	inline static void setScreenSize( const Vector2d& _sz ) { glfwSetWindowSize( (unsigned int) _sz.getX(), (unsigned int) _sz.getY() ); screensize = _sz;}

	//! Get screen size
	inline static const Vector2d getScreenSize() { return screensize; }

    //! Set the resize callback function.
    /*!
        By default this is set to a function that prevents window resizing. RenderSystem usually registers
        its callback instead.
    */
    inline static void setResizeCallback( boost::function< void( Vector2d ) > _f = boost::function< void( Vector2d ) >( &WindowManager::noResizeCallback ) ) { resizefunc = _f; }

    //! Get the resize callback function.
    inline static boost::function< void( Vector2d ) > getResizeCallback( ) { return resizefunc; }

	//! Iconify
	inline static void iconify() { glfwIconifyWindow(); }

	//! Restore
	inline static void restore() { glfwRestoreWindow(); }

    /*! Set Cursor Visibility.
        Can hide or show the mouse cursor. Hiding it has three effects: The mouse cursor is invisible, the mouse is confined to the screen,
        and coordinates are no longer limited to the window size. By default, the mouse is hidden in fullscreen, but otherwise visible.
    */
    inline static void setCursorVisible(const bool _v) { _v ? glfwEnable( GLFW_MOUSE_CURSOR ) : glfwDisable( GLFW_MOUSE_CURSOR ); }

	//! Swap Buffers and Update Events.
	inline static void swapBuffers() 
	{
		EventReceiver::updateEvents(); //Must be called first, as the next call will tell it all about the new events.
		glfwSwapBuffers(); 
	}

protected:

    //! Internal screen size record.
    static Vector2d screensize;
    
    //! Window Resize callback function object.
    static boost::function< void ( Vector2d ) > resizefunc;

    //! Window Resize dispatch
    static void windowResizeDispatch( int width, int height )
    {
        if( resizefunc )
            resizefunc( Vector2d( (float) width, (float) height ) );
    }

    //! Default window resize callback, it disables resizing.
    static void noResizeCallback( Vector2d _sz )
    {
        setScreenSize( getScreenSize() );
    }
    
};

}

#endif //__PHWINDOWMANAGER_H__