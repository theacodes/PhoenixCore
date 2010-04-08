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
	glfwSetKeyCallback( &GLFWWindowManager::glfwKeyboardCallback );
	glfwSetCharCallback( &GLFWWindowManager::glfwCharacterCallback );
	glfwSetMouseButtonCallback( &GLFWWindowManager::glfwKeyboardCallback );
	glfwSetMousePosCallback( &GLFWWindowManager::glfwMousePosCallback );
	glfwSetWindowCloseCallback( &GLFWWindowManager::glfwWindowCloseCallback );
	glfwSetMouseWheelCallback( &GLFWWindowManager::glfwMouseWheelPosCallback );
    glfwSetWindowSizeCallback( &GLFWWindowManager::glfwWindowResizeCallback );

	// Disable key repeat; event receiver manages that.
	glfwDisable(GLFW_KEY_REPEAT);

}

//! Window Resize callback (from GLFW).
void GLFWWindowManager::glfwWindowResizeCallback( int width, int height )
{
	WindowManagerPtr wm = WindowManager::Instance();

    if( wm->getResizeCallback() )
        (wm->getResizeCallback())( Vector2d( (float) width, (float) height ) );
}

//! Keyboard callback (from GLFW).
void GLFWWindowManager::glfwKeyboardCallback( int key, int action )
{
	WindowEvent e;
	e.type = WET_KEY;
	e.key = key;
	e.state = action == GLFW_PRESS ? true : false;
	Instance()->signal(e);
}

//! Character callback (from GLFW).
void GLFWWindowManager::glfwCharacterCallback( int key, int action )
{
	if( action == GLFW_PRESS ){
		WindowEvent e;
		e.type = WET_CHAR;
		e.key = key;
		e.state = true;
		Instance()->signal(e);
	}
}


//! Mouse position callback (from GLFW).
void GLFWWindowManager::glfwMousePosCallback( int x, int y )
{
	WindowEvent e;
	e.type = WET_MOUSE_POSITION;
	e.state = true;
	e.mouse_position = Vector2d( float(x), float(y) );
	Instance()->signal(e);
}

//! Window callback (from GLFW).
int GLFWWindowManager::glfwWindowCloseCallback()
{
	WindowEvent e;
	e.type = WET_CLOSE;
	e.state = true;
	Instance()->signal(e);
	return false;
}

//! Mouse wheel callback (from GLFW).
void GLFWWindowManager::glfwMouseWheelPosCallback( int pos )
{
	WindowEvent e;
	e.type = WET_MOUSE_WHEEL;
	e.state = true;
	e.mouse_wheel = pos;
	Instance()->signal(e);
}