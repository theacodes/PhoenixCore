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
	inline static void open( Vector2d _sz = Vector2d( 640, 480 ), bool _f = false )
	{

        // Set our internal screen size variable.
        screensize = _sz;

		// No GLFW functions may be called before this
		glfwInit();

		// Important defines
		#define RED_BITS 8
		#define BLUE_BITS 8
		#define GREEN_BITS 8
		#define ALPHA_BITS 8
		#define STENCIL_BITS 0
		#ifdef DISABLE_DEPTHBUFFER
			#define DEPTH_BITS 0
		#else
			#define DEPTH_BITS 8
		#endif

		// No resize
		//glfwOpenWindowHint( GLFW_WINDOW_NO_RESIZE, GL_TRUE ); 

		if(_f)
		{
			glfwOpenWindow(int(_sz.getX()), int(_sz.getY()), RED_BITS, BLUE_BITS, GREEN_BITS, ALPHA_BITS, DEPTH_BITS, STENCIL_BITS, GLFW_FULLSCREEN);
		}
		else
		{
			glfwOpenWindow(int(_sz.getX()), int(_sz.getY()), RED_BITS, BLUE_BITS, GREEN_BITS, ALPHA_BITS, DEPTH_BITS, STENCIL_BITS, GLFW_WINDOW);
		}

		// Now, disable vsync.
		glfwSwapInterval( 0 );

		// Set the window caption
		setWindowCaption("PhoenixCore v0.1 Alpha");

		// set GLFW callbacks
		glfwSetKeyCallback( &EventReceiver::KeyboardCallback );
		glfwSetMouseButtonCallback( &EventReceiver::MouseButtonCallback );
		glfwSetMousePosCallback( &EventReceiver::MousePosCallback );
		glfwSetWindowCloseCallback( &EventReceiver::WindowCloseCallback );
		glfwSetMouseWheelCallback( &EventReceiver::MouseWheelPosCallback );
        glfwSetWindowSizeCallback( &WindowManager::windowResizeDispatch );

		// Disable key repeat; event receiver manages that.
		glfwDisable(GLFW_KEY_REPEAT);

	}

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