/*

Copyright (c) 2007, Jonathan Wayne Parrott, Denzel Morris.

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

#include "PhEventHandle.h"

using namespace phoenix;

//! Array to store key info.
bool phoenix::PhEventHandler::keys[512];

//! Array to store mouse info.
bool phoenix::PhEventHandler::mousebutton[16];

//!array to store info on if a key was just pressed.
bool phoenix::PhEventHandler::keysdown[512];

//!array to store info on if a mouse button was just pressed.
bool phoenix::PhEventHandler::mousebuttondown[16];

//!if the user "X"ed out of the window, this is true.
bool phoenix::PhEventHandler::quit = false;

//!stores the mouse's position.
PhVector2d phoenix::PhEventHandler::mousepos = PhVector2d(0,0);

//!stores the mouse's wheel position.
int phoenix::PhEventHandler::mousewheelpos = 0;

////////////////////////////////////////////////////////////////////////////////
//Construct
////////////////////////////////////////////////////////////////////////////////

PhEventHandler::PhEventHandler()
{

    //init the arrays
    for (int i=0;i<513;i++)
    {
        keys[i]=0;
        keysdown[i]=0;
    }

    for (int i=0;i<16;i++)
    {
        mousebutton[i]=0;
        mousebuttondown[i]=0;
    }

}

////////////////////////////////////////////////////////////////////////////////
//Updates the events, this is normally called in the run() function of
//PhRenderSystem
////////////////////////////////////////////////////////////////////////////////

void PhEventHandler::updateEvents()
{
	//clear the keydown array
	for (int i=0;i<513;i++)
	{
		keysdown[i]=0;
	}

	for (int i=0;i<16;i++)
	{
		mousebuttondown[i]=0;
	}
}

////////////////////////////////////////////////////////////////////////////////
// Mouse & Keyboard callback (for GLFW)
////////////////////////////////////////////////////////////////////////////////

void PhEventHandler::KeyboardCallback( int key, int action )
{
	if (action == GLFW_PRESS) {
    	keysdown[key]=true;
    	keys[key]=true;
    } else if (action == GLFW_RELEASE) {
    	keys[key] = false;
	}
}

void PhEventHandler::MouseButtonCallback( int key, int action )
{
	if (action == GLFW_PRESS) {
		mousebuttondown[key]=true;
		mousebutton[key]=true;
	} else if (action == GLFW_RELEASE) {
		mousebutton[key] = false;
	}
}

void PhEventHandler::MousePosCallback( int x, int y)
{
	mousepos.setX(float(x));
	mousepos.setY(float(y));
}

int PhEventHandler::WindowCloseCallback()
{
	quit = true;
	return GL_TRUE;
}

void PhEventHandler::MouseWheelPosCallback( int pos )
{
	mousewheelpos = pos;
}


////////////////////////////////////////////////////////////////////////////////
//Get key function, it returns true if the given key was pressed
////////////////////////////////////////////////////////////////////////////////

const bool& PhEventHandler::getKey(const PhKey& a) const
{
    return keys[a];
}

const bool& PhEventHandler::getKeyPressed(const PhKey& a) const
{
    return keysdown[a];
}

////////////////////////////////////////////////////////////////////////////////
//Get key function, it returns true if the given key was pressed
////////////////////////////////////////////////////////////////////////////////

const bool& PhEventHandler::getMouseButton(const PhMouseKey& a) const
{
    return mousebutton[a];
}

const bool& PhEventHandler::getMouseButtonPressed(const PhMouseKey& a) const
{
    return mousebuttondown[a];
}

////////////////////////////////////////////////////////////////////////////////
//Get mouse wheel position function, returns the amount turned on the axis
////////////////////////////////////////////////////////////////////////////////

const int& PhEventHandler::getMouseWheelPosition() const
{
	return mousewheelpos;
}

////////////////////////////////////////////////////////////////////////////////
//Get mouse position functions
////////////////////////////////////////////////////////////////////////////////

const PhVector2d& PhEventHandler::getMousePosition() const
{
    return mousepos;
}

////////////////////////////////////////////////////////////////////////////////
//This function will  return true if the user closed the window
////////////////////////////////////////////////////////////////////////////////

const bool& PhEventHandler::getWindowClosed() const
{
    return quit;
}
