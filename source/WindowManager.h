/*

Copyright (c) 2009, Jonathan Wayne Parrott

Please see the license.txt file included with this source
distribution for more information.

*/

#ifndef __PHWINDOWMANAGER_H__
#define __PHWINDOWMANAGER_H__

#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>
#include "config.h"
#include "EventReceiver.h"
#include "Vector2d.h"

namespace phoenix
{

//! Abstract Window Manager
/*!
	This abstract class defines the interface for window manager. The default window manager
	in phoenix is GLFWWindowManager. The window manager is responsible for creating and managing the OpenGL
	context and dispatching events. This class is a Singleton. As such, it ( and it's derivitives )
	can only be instanced via the Instance() static function.
*/
class WindowManager
{
public:

	//! Bad instance exception.
	class BadInstance {};

	//! Gets the current window manager instance.
	/*!
		If no window manager exists, this function will throw. Subclasses should
		define their own Instance.
		\throws BadIntance if no concrete instance can be made.
	*/
	static boost::shared_ptr<WindowManager> Instance( ){
		if( !instance ) throw BadInstance();
		return instance;
	}

	//! Destructor
	virtual ~WindowManager(){
	}

	//! Sets the current window manager instance.

	/*!
		Should create a new window and initialize OpenGL.
		\param _sz The size of the window.
		\param _f Fullscreen.
	*/
	virtual bool open( const Vector2d& _sz = Vector2d( 640, 480 ), const bool _f = false ) = 0;

	/*!
		Closes and terminates the window.
	*/
	virtual void close() = 0;

	//! Sets the window's title.
    virtual void setWindowTitle(const std::string& _str) = 0;

	//! Sets the window's size
	inline virtual void setWindowSize( const Vector2d& _sz ){ screensize = _sz; }

	//! Gets the screen's size size
	inline virtual const Vector2d& getWindowSize() { return screensize; }

    //! Set the resize callback function.
    /*!
        By default this is set to a function that prevents window resizing. RenderSystem usually registers
        its own callback instead.
    */
    inline void setResizeCallback( const boost::function< void( Vector2d ) >& _f = boost::function< void( Vector2d ) >( &WindowManager::noResizeCallback ) ) { resizefunc = _f; }

    //! Gets the resize callback function.
    inline const boost::function< void( Vector2d ) >& getResizeCallback( ) { return resizefunc; }

	//! Iconify
	virtual void iconify() = 0;

	//! Restore
	virtual void restore() = 0;

    //! Set Cursor Visibility.
    inline virtual void setCursorVisible(const bool _v)  = 0;

	//! Updates the window (swapping buffers, processing events, etc. )
	inline virtual void update() = 0;

protected:

	WindowManager()
		: screensize(), resizefunc( &WindowManager::noResizeCallback )
	{}

	//! Singleton Instance
	static boost::shared_ptr<WindowManager> instance;

    //! Internal screen size record.
    Vector2d screensize;
    
    //! Window Resize callback function object.
    boost::function< void ( Vector2d ) > resizefunc;

    //! Default window resize callback, it disables resizing.
    static void noResizeCallback( Vector2d _sz )
    {
		boost::shared_ptr<WindowManager> wm = Instance();
        wm->setWindowSize( wm->getWindowSize() );
    }
    
};

typedef boost::shared_ptr<WindowManager> WindowManagerPtr;

}

#endif //__PHGLFWWINDOWMANAGER_H__