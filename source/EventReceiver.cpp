/*

Copyright (c) 2009, Jonathan Wayne Parrott

Please see the license.txt file included with this source
distribution for more information.

*/

#include "EventReceiver.h"

using namespace phoenix;

//! Array to store key info.
bool phoenix::EventReceiver::keys[512];

//! Array to store mouse info.
bool phoenix::EventReceiver::mousebutton[16];

//!array to store info on if a key was just pressed.
bool phoenix::EventReceiver::keysdown[512];

//!array to store info on if a mouse button was just pressed.
bool phoenix::EventReceiver::mousebuttondown[16];

//!if the user "X"ed out of the window, this is true.
bool phoenix::EventReceiver::quit = false;

//!stores the mouse's position.
Vector2d phoenix::EventReceiver::mousepos = Vector2d(0,0);

//!stores the mouse's wheel position.
int phoenix::EventReceiver::mousewheelpos = 0;

//!stores the keyboard string.
std::string phoenix::EventReceiver::keyboardstring = std::string("");

////////////////////////////////////////////////////////////////////////////////
//Construct
////////////////////////////////////////////////////////////////////////////////

EventReceiver::EventReceiver()
{

    //init the arrays
    for (int i=0;i<512;i++)
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
//RenderSystem
////////////////////////////////////////////////////////////////////////////////

void EventReceiver::updateEvents()
{
	//clear the keydown array
	for (int i=0;i<512;i++)
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

void EventReceiver::KeyboardCallback( int key, int action )
{
	if (action == GLFW_PRESS) {
    	keysdown[key]=true;
    	keys[key]=true;

		//backspace for keyboard strings.
		if( key == PHK_BACKSPACE ){
			keyboardstring = keyboardstring.substr(0, keyboardstring.length() - 1);
		}

    } else if (action == GLFW_RELEASE) {
    	keys[key] = false;
    	keysdown[key] = true;
	}
}

void EventReceiver::CharacterCallback( int key, int action )
{
	if (action == GLFW_PRESS) {
		keyboardstring += key;
	}
}

void EventReceiver::MouseButtonCallback( int key, int action )
{
	if (action == GLFW_PRESS) {
		mousebutton[key]=true;
		mousebuttondown[key]=true;
	} else if (action == GLFW_RELEASE) {
		mousebutton[key] = false;
		mousebuttondown[key]=true;
	}
}

