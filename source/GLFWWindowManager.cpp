#include "GLFWWindowManager.h"

using namespace phoenix;

/*!
    Open function.
*/
bool GLFWWindowManager::open( const Vector2d& _sz, const bool _f )
{

    // Set our internal screen size variable.
    screensize = _sz;

	// No GLFW functions may be called before this
	if( !glfwInit() ) return false;

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
	setWindowTitle( PHOENIXCORE_VERSION );

	// Set GLFW event callbacks
	glfwSetKeyCallback( &EventReceiver::KeyboardCallback );
	glfwSetCharCallback( &EventReceiver::CharacterCallback );
	glfwSetMouseButtonCallback( &EventReceiver::MouseButtonCallback );
	glfwSetMousePosCallback( &EventReceiver::MousePosCallback );
	glfwSetWindowCloseCallback( &EventReceiver::WindowCloseCallback );
	glfwSetMouseWheelCallback( &EventReceiver::MouseWheelPosCallback );
    glfwSetWindowSizeCallback( &GLFWWindowManager::windowResizeCallback );

	// Disable key repeat; event receiver manages that.
	glfwDisable(GLFW_KEY_REPEAT);

}

//! Window Resize callback (from GLFW).
static void GLFWWindowManager::glfwWindowResizeCallback( int width, int height )
{
	boost::shared_ptr<WindowManager> wm = WindowManager::Instance();

    if( wm->getResizeCallback() )
        (wm->getResizeCallback())( Vector2d( (float) width, (float) height ) );
}