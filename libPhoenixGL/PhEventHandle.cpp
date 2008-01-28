/*

Copyright (c) 2007, Jonathan Wayne Parrott.

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
        /*
        //Poll SDL for an event
        while ( SDL_PollEvent( &event ) )
        {

            //If a key was pressed
            if ( event.type == SDL_KEYDOWN )
            {
                keys[event.key.keysym.sym]=true;
                keysdown[event.key.keysym.sym]=true;
            }

            //Released
            if ( event.type == SDL_KEYUP )
            {
                keys[event.key.keysym.sym]=false;
            }

            //if user closed the window
            if ( event.type == SDL_QUIT )
            {
                quit = true;
            }

            //mouse motion
            if ( event.type == SDL_MOUSEMOTION )
            {
                mousepos.setX(float(event.motion.x));
                mousepos.setY(float(event.motion.y));
            }

            //mouse button
            if ( event.type == SDL_MOUSEBUTTONDOWN )
            {
                mousebutton[int(event.button.button)] = true;
                mousebuttondown[int(event.button.button)] = true;
            }

            if ( event.type == SDL_MOUSEBUTTONUP )
            {
                mousebutton[int(event.button.button)] = false;
            }

        }
    */
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

bool PhEventHandler::getKey(PhKey a)
{
    return keys[a];
}

bool PhEventHandler::getKeyPressed(PhKey a)
{
    return keysdown[a];
}

////////////////////////////////////////////////////////////////////////////////
//Get key function, it returns true if the given key was pressed
////////////////////////////////////////////////////////////////////////////////

bool PhEventHandler::getMouseButton(PhMouseKey a)
{
    return mousebutton[a];
}

bool PhEventHandler::getMouseButtonPressed(PhMouseKey a)
{
    return mousebuttondown[a];
}

////////////////////////////////////////////////////////////////////////////////
//Get mouse wheel position function, returns the amount turned on the axis
////////////////////////////////////////////////////////////////////////////////

int PhEventHandler::getMouseWheelPosition()
{
	return mousewheelpos;
}

////////////////////////////////////////////////////////////////////////////////
//Get mouse position functions
////////////////////////////////////////////////////////////////////////////////

PhVector2d PhEventHandler::getMousePosition()
{
    return mousepos;
}

////////////////////////////////////////////////////////////////////////////////
//This function will  return true if the user closed the window
////////////////////////////////////////////////////////////////////////////////

bool PhEventHandler::returnQuit()
{
    return quit;
}
