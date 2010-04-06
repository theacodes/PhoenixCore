/*

Copyright (c) 2009, Jonathan Wayne Parrott

Please see the license.txt file included with this source
distribution for more information.

*/

#ifndef __PHGLFWWINDOWMANAGER_H__
#define __PHGLFWWINDOWMANAGER_H__

#include <GL/glfw.h>
#include <boost/function.hpp>
#include "WindowManager.h"
#include "config.h"
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
class GLFWWindowManager
	: public WindowManager
{
public:

	//! Gets the current window manager instance.
	/*!
		If no window manager exists, this function will throw. Subclasses should
		define their own Instance.
	*/
	static boost::shared_ptr<WindowManager> Instance( ){
		if( !instance ){
			instance = WindowManagerPtr( new GLFWWindowManager );
		}
		return instance;
	}

	/*!
		Creates a new window and initializes OpenGL. Also sets up callbacks for
		key events.
		\param _sz The size of the window.
		\param _f Fullscreen.
	*/
	virtual bool open( Vector2d _sz = Vector2d( 640, 480 ), bool _f = false );

	/*!
		Closes and terminates the window.
	*/
	inline virtual void close()
	{
	    glfwCloseWindow();
		glfwTerminate();
	}

	//! Set window caption.
    inline virtual void setWindowTitle(const std::string& _str) { glfwSetWindowTitle(_str.c_str()); }

	//! Set screen size
	inline virtual void setWindowSize( const Vector2d& _sz ) { 
		glfwSetWindowSize( (unsigned int) _sz.getX(), (unsigned int) _sz.getY() ); 
		WindowManager::setWindowSize(_sz);
	}

	//! Iconify
	inline virtual void iconify() { glfwIconifyWindow(); }

	//! Restore
	inline virtual void restore() { glfwRestoreWindow(); }

    /*! Set Cursor Visibility.
        Can hide or show the mouse cursor. Hiding it has three effects: The mouse cursor is invisible, the mouse is confined to the screen,
        and coordinates are no longer limited to the window size. By default, the mouse is hidden in fullscreen, but otherwise visible.
    */
    inline virtual void setCursorVisible(const bool _v) { _v ? glfwEnable( GLFW_MOUSE_CURSOR ) : glfwDisable( GLFW_MOUSE_CURSOR ); }

	//! Swap Buffers and Update Events.
	inline virtual void update() 
	{
		EventReceiver::updateEvents(); //Must be called first, as the next call will tell it all about the new events.
		glfwSwapBuffers(); 
	}

protected:

	GLFWWindowManager()
		: WindowManager()
	{}

    //! Window Resize dispatch
    static void windowResizeDispatch( int width, int height )
    {
		boost::shared_ptr<WindowManager> wm = WindowManager::Instance();

        if( wm->getResizeCallback() )
            (wm->getResizeCallback())( Vector2d( (float) width, (float) height ) );
    }
    
};

}

#endif //__PHGLFWWINDOWMANAGER_H__