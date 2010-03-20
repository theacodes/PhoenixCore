#include "WindowManager.h"

using namespace phoenix;

/*!
    Open function.
*/
void WindowManager::open( Vector2d _sz, bool _f )
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

	if(_f)
	{
		glfwOpenWindow(int(_sz.getX()), int(_sz.getY()), RED_BITS, BLUE_BITS, GREEN_BITS, ALPHA_BITS, DEPTH_BITS, STENCIL_BITS, GLFW_FULLSCREEN);
	}
	else
	{
		glfwOpenWindow(int(_sz.getX()), int(_sz.getY()), RED_BITS, BLUE_BITS, GREEN_BITS, ALPHA_BITS, DEPTH_BITS, STENCIL_BITS, GLFW_WINDOW);
	}

	// Disable vsync.
	glfwSwapInterval( 0 );

	// Set the window caption
	setWindowCaption( PHOENIXCORE_VERSION );

	// Set GLFW event callbacks
	glfwSetKeyCallback( &EventReceiver::KeyboardCallback );
	glfwSetCharCallback( &EventReceiver::CharacterCallback );
	glfwSetMouseButtonCallback( &EventReceiver::MouseButtonCallback );
	glfwSetMousePosCallback( &EventReceiver::MousePosCallback );
	glfwSetWindowCloseCallback( &EventReceiver::WindowCloseCallback );
	glfwSetMouseWheelCallback( &EventReceiver::MouseWheelPosCallback );
    glfwSetWindowSizeCallback( &WindowManager::windowResizeDispatch );

	// Disable key repeat; event receiver manages that.
	glfwDisable(GLFW_KEY_REPEAT);

}

//! Static initialization.
Vector2d WindowManager::screensize = Vector2d(0,0);
boost::function< void (Vector2d) > WindowManager::resizefunc( &WindowManager::noResizeCallback );