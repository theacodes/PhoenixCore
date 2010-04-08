/*

Copyright (c) 2009, Jonathan Wayne Parrott

Please see the license.txt file included with this source
distribution for more information.

*/

#include "EventReceiver.h"

using namespace phoenix;

//! Connection to WindowManager
boost::signals2::connection phoenix::EventReceiver::event_connection;

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

void EventReceiver::update()
{

	// Connect to the window manager.
	if( ! event_connection.connected() ){
		try{
			event_connection = WindowManager::Instance()->listen( &EventReceiver::onEvent );
		}catch( WindowManager::BadInstance ){
		}
	}

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
// On event
////////////////////////////////////////////////////////////////////////////////
void EventReceiver::onEvent( const WindowEvent& e )
{
	switch( e.type ){
		case WET_CLOSE:
			quit = true; break;

		case WET_KEY:
			{
				if( e.key > 2 ) //Keyboard
				{
					if (e.state == true) {
						keysdown[e.key]=true;
						keys[e.key]=true;

						//backspace for keyboard strings.
						if( e.key == PHK_BACKSPACE ){
							keyboardstring = keyboardstring.substr(0, keyboardstring.length() - 1);
						}

					} else {
						keys[e.key] = false;
						keysdown[e.key] = true;
					}
				}else{ //Mouse
					if ( e.state == true ) {
						mousebutton[ e.key ]=true;
						mousebuttondown[ e.key ]=true;
					} else if ( e.state == false) {
						mousebutton[ e.key ] = false;
						mousebuttondown[ e.key ]=true;
					}
				}
			} break;

		case WET_CHAR:
			{
				keyboardstring += e.key;
			}break;

		case WET_MOUSE_POSITION:
			{
				mousepos = e.mouse_position;
			}break;

		case WET_MOUSE_WHEEL:
			{
				mousewheelpos = e.mouse_wheel;
			}

		default:
			break;
	}
}