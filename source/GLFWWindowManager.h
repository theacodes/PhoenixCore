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

//! GLFW Window Manager Implementation
/*!
	This class implements the GLFW window manager and provides translations
	for Events.
*/
class GLFWWindowManager
	: public WindowManager
{
public:

	//! Instance.
	static boost::shared_ptr<WindowManager> Instance( ){
		if( !instance ){
			instance = WindowManagerPtr( new GLFWWindowManager );
		}
		return instance;
	}

	/*! Open Command.
		Creates a new window and initializes OpenGL. Also sets up callbacks for
		key events.
		\param _sz The size of the window.
		\param _f Fullscreen.
	*/
	virtual bool open( const Vector2d& _sz = Vector2d( 640, 480 ), const bool _f = false );

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

	//! Set window size
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
		EventReceiver::update(); //Must be called first, as the next call will tell it all about the new events.
		glfwSwapBuffers(); 
	}

protected:

	GLFWWindowManager()
		: WindowManager()
	{}

    //! Window Resize callback (from GLFW).
    static void glfwWindowResizeCallback( int width, int height );

	//! Keyboard callback (from GLFW).
    static void glfwKeyboardCallback( int key, int action );

	//! Character callback (from GLFW).
	static void glfwCharacterCallback( int key, int action );

    //! Mouse position callback (from GLFW).
    static void glfwMousePosCallback( int x, int y );

    //! Window callback (from GLFW).
    static int glfwWindowCloseCallback();

    //! Mouse wheel callback (from GLFW).
    static void glfwMouseWheelPosCallback( int pos );
    
};

}

#endif //__PHGLFWWINDOWMANAGER_H__